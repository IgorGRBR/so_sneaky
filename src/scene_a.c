/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:01:38 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/24 11:01:39 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slscene.h"
#include <stdlib.h>
#include <fcntl.h>
#include "ylib.h"
#include "slactor.h"

static void	init_scene_stuff(t_scene *scene)
{
	int	i;

	scene->grid = (t_node **)malloc(sizeof(t_node *) * scene->size.y);
	i = 0;
	while (i < scene->size.y)
	{
		scene->grid[i] = (t_node *)malloc(sizeof(t_node) * scene->size.x);
		i++;
	}
	scene->actors = list_new();
	scene->patrols = list_new();
	scene_setup_player_state(scene);
	scene->required_item_count = 0;
	scene->update_status = CONTINUE_STATUS;
	scene->camera_focus_actor = YNULL;
}

static void	setup_node(t_scene *scene, t_ivec2 pos, char t)
{
	t_node	node;

	node = (t_node){.tile = EMPTY, .actor = YNULL, .item = NO_ITEM};
	if (t == '1')
		node.tile = EMPTY;
	else
	{
		node.tile = FLOOR;
		if (t == 'C')
			node.item = PURPLE_KEYCARD;
		else if (t == 'E')
			node.tile = EXIT_CLOSED;
		else if (t == 'P')
		{
			scene->player = actor_new(pos, DOWN, PLAYER);
			list_insert(scene->actors, scene->player);
			node.actor = scene->player;
			scene->camera_focus_actor = scene->player;
		}
		else if (t != '0')
			error_exit("Invalid tile type");
	}
	scene->grid[pos.y][pos.x] = node;
}

static void	parse_ber(t_scene *scene, t_list *lines)
{
	t_string	*line;
	t_ivec2		i;

	scene->size.y = lines->size;
	line = list_get(lines, 0);
	scene->size.x = line->size;
	init_scene_stuff(scene);
	i = ivec2_zero();
	while (i.y < scene->size.y)
	{
		i.x = 0;
		line = list_get(lines, i.y);
		if (line->size != (t_uint)scene->size.x)
			error_exit("Level map must be rectangular");
		while (i.x < scene->size.x)
		{
			setup_node(scene, i, line->cstr[i.x]);
			i.x++;
		}
		i.y++;
	}
	(scene_setup_tiles_auto(scene), verify_scene(scene));
}

static t_bool	line_filter(t_string *line)
{
	t_string	*trimmed;
	t_bool		result;

	trimmed = string_trim_cstr(line, " \n");
	result = trimmed->cstr[0] == '#';
	string_delete(trimmed);
	if (result)
		string_delete(line);
	return (result);
}

t_scene	*scene_new(char *path, t_game_data *game)
{
	t_scene	*scene;
	t_list	*lines;
	t_list	*ext_lines;

	scene = (t_scene *)malloc(sizeof(t_scene));
	scene->asset_path = YNULL;
	lines = read_file_to_lines_cstr(path, O_RDONLY);
	if (!lines)
		(free(scene), error_exit("Specified .ber file was not found"));
	(parse_ber(scene, lines), list_apply(lines, (t_apply_func)string_delete));
	(list_delete(lines), path = cstr_join(path, ".ext"));
	ext_lines = read_file_to_lines_cstr(path, O_RDONLY);
	if (ext_lines)
	{
		list_filter(ext_lines, (t_filter_func)line_filter);
		scene_parse_ext(scene, ext_lines);
		list_apply(ext_lines, (t_apply_func)string_delete);
		list_delete(ext_lines);
	}
	setup_scene_assets(scene, game->assets, &game->mlx_ctx);
	(free(path), verify_scene(scene), scene_setup_keys(scene, game));
	return (scene);
}
