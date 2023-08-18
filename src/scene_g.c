/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_g.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:04:58 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/06/05 15:04:59 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slmlx.h"
#include "slscene.h"
#include "slscene_types.h"
#include "ycstr.h"
#include "ylib.h"
#include "ylist.h"
#include "ystring.h"
#include "ytypes.h"
#include "yvec2.h"
#include <stdlib.h>
#include "slactor.h"

static const char				*g_tags = "atl";
static const char				*g_objects = "0^M<vlbekotd";

static t_ext_tag	*parse_tag(t_list *str)
{
	t_ext_tag	*tag;

	if (str->size < 3)
		error_exit("Invalid data tag string in EXT file");
	tag = (t_ext_tag *)malloc(sizeof (t_ext_tag));
	tag->type = ((t_string *)list_get(str, 1))->cstr[0];
	tag->data = cstr_atoi(((t_string *)list_get(str, 2))->cstr);
	return (tag);
}

static const t_item				g_keycards[3] = {
	PURPLE_KEYCARD,
	GREEN_KEYCARD,
	ORANGE_KEYCARD,
};

static const t_walk_strategy	g_walk_strats[] = {
	RANDOM_WALK,
	HUG_WALL_WALK,
	LAZY_TURNING_WALK,
	RANDOM_WALK,
};

static void	apply_tag(t_scene *scene, t_ivec2 pos, char type, t_uint tag)
{
	if (type == 'k' && scene->grid[pos.y][pos.x].item == PURPLE_KEYCARD)
		scene->grid[pos.y][pos.x].item = g_keycards[tag];
	if (type == 'e')
	{
		scene->grid[pos.y][pos.x].actor->walk_strategy = g_walk_strats[tag % 4];
		scene->grid[pos.y][pos.x].actor->direction = (tag / 4) % 4;
		scene->grid[pos.y][pos.x].actor->turn_preference = (tag / 16) % 4;
	}
}

static void	apply_node(t_scene *scene, t_ivec2 pos, t_list_iter *tag_it,
	char c)
{
	if (c == 'e')
	{
		scene->grid[pos.y][pos.x].actor = actor_new(pos, DOWN, ENEMY);
		list_insert(scene->actors, scene->grid[pos.y][pos.x].actor);
		list_insert(scene->patrols, scene->grid[pos.y][pos.x].actor);
	}
	if (c == 'd')
		_scene_setup_door(scene, pos, ((t_ext_tag *)tag_it->value)->data);
	if (tag_it->value && ((t_ext_tag *)tag_it->value)->type == c)
	{
		apply_tag(scene, pos, c, ((t_ext_tag *)tag_it->value)->data);
		list_iter_next(tag_it);
	}
}

static void	parse_level_data(t_scene *scene, t_list *tags, t_list_iter *lines)
{
	t_ivec2		a;
	t_list_iter	it;
	t_string	*line;

	a = ivec2_new(-1, -1);
	it = list_iter_first(tags);
	while (++a.y < scene->size.y && list_iter_next(lines))
	{
		a.x = -1;
		line = lines->value;
		while (++a.x < scene->size.x)
		{
			if (!char_in_cstr(line->cstr[a.x], g_objects))
				error_exit("Unknown object type in EXT file");
			apply_node(scene, a, &it, line->cstr[a.x]);
		}
	}
}

// (tags is a list of unsigned ints)
void	scene_parse_ext(t_scene *scene, t_list *ext_lines)
{
	t_list_iter	it;
	t_list		*line;
	t_list		*tags;

	it = list_iter(ext_lines);
	tags = list_new();
	while (list_iter_next(&it))
	{
		line = string_split(it.value, ' ');
		if (line->size == 0
			|| !char_in_cstr(((t_string *)list_get(line, 0))->cstr[0],
				g_tags))
			error_exit("Unknown tag encountered in EXT file");
		if (((t_string *)list_get(line, 0))->cstr[0] == 't')
			list_insert(tags, parse_tag(line));
		else if (((t_string *)list_get(line, 0))->cstr[0] == 'a'
			&& scene->asset_path == YNULL)
			scene->asset_path = string_copy(list_get(line, 1));
		else if (((t_string *)list_get(line, 0))->cstr[0] == 'l')
			parse_level_data(scene, tags, &it);
		(list_apply(line, (t_apply_func)string_delete), list_delete(line));
	}
	(list_apply(tags, (t_apply_func)free), list_delete(tags));
}
