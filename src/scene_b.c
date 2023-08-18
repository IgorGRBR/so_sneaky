/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:26:41 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/24 13:26:42 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slscene.h"
#include "slscene_types.h"
#include "ystring.h"
#include "slgame.h"
#include <stdlib.h>
#include "ylist.h"
#include "slactor.h"

void	scene_delete(t_scene *scene)
{
	t_uint	i[2];

	i[0] = -1;
	while (++i[0] < (t_uint)scene->size.y)
		free(scene->grid[i[0]]);
	if (scene->asset_path)
		string_delete(scene->asset_path);
	i[0] = 0;
	while (i[0] < ACTOR_TYPE_COUNT)
	{
		i[1] = 0;
		while (i[1] < ACTOR_STATE_COUNT)
		{
			list_delete(scene->actor_sprites[i[0]][i[1]][0]);
			list_delete(scene->actor_sprites[i[0]][i[1]][1]);
			list_delete(scene->actor_sprites[i[0]][i[1]][2]);
			list_delete(scene->actor_sprites[i[0]][i[1]][3]);
			i[1]++;
		}
		i[0]++;
	}
	list_delete(scene->patrols);
	list_apply(scene->actors, (t_apply_func)actor_delete);
	(list_delete(scene->actors), free(scene->grid), free(scene));
}

static void	increment_counters(t_scene *scene, t_ivec2 pos, t_uint counter[3])
{
	t_node	*node;

	node = &scene->grid[pos.y][pos.x];
	if (node->tile == EXIT_CLOSED)
	{
		counter[1]++;
		scene->exit_pos = pos;
	}
	if (node->actor == scene->player)
		counter[0]++;
	if (node->item == PURPLE_KEYCARD
		|| node->item == GREEN_KEYCARD
		|| node->item == ORANGE_KEYCARD)
		counter[2]++;
}

static void	verify_objects(t_scene *scene)
{
	t_ivec2	a;
	t_uint	counter[3];

	a.y = -1;
	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	while (++a.y < scene->size.y)
	{
		a.x = -1;
		while (++a.x < scene->size.x)
			increment_counters(scene, a, counter);
	}
	if (counter[0] != 1)
		error_exit("Level must only contain 1 player start");
	if (counter[1] != 1)
		error_exit("Level must only contain 1 exit");
	if (counter[2] < 1)
		error_exit("Level must contain at least 1 collectible item");
	scene->required_item_count = counter[2];
}

void	verify_scene(t_scene *scene)
{
	t_ivec2	a;

	a = ivec2_zero();
	a.y = scene->size.y - 1;
	while (a.x < scene->size.x)
	{
		if (scene->grid[0][a.x].tile == FLOOR
			|| scene->grid[a.y][a.x].tile == FLOOR)
			error_exit("Level must be confined with solid walls");
		a.x++;
	}
	a.x = scene->size.x - 1;
	a.y = 0;
	while (a.y < scene->size.y)
	{
		if (scene->grid[a.y][0].tile == FLOOR
			|| scene->grid[a.y][a.x].tile == FLOOR)
			error_exit("Level must be confined with solid walls");
		a.y++;
	}
	verify_objects(scene);
}

void	scene_setup_keys(t_scene *scene, t_game_data *game)
{
	t_uint	i;

	scene->keys.map[KEY_UP] = game->config.up_keycode;
	scene->keys.map[KEY_RIGHT] = game->config.right_keycode;
	scene->keys.map[KEY_DOWN] = game->config.down_keycode;
	scene->keys.map[KEY_LEFT] = game->config.left_keycode;
	scene->keys.map[KEY_ACTION] = game->config.action_keycode;
	scene->keys.map[KEY_CANCEL] = game->config.cancel_keycode;
	i = 0;
	while (i < KEYCOUNT)
	{
		scene->keys.down[i] = FALSE;
		i++;
	}
}
