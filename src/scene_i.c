/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:28:48 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/06/12 14:28:50 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slscene.h"
#include "slscene_types.h"
#include "ylib.h"
#include "slactor.h"

// I'm going to run out of the entire alphabet like this

static const t_tile	g_hdoors[] = {
	PURPLE_DOOR_CLOSED_H1,
	GREEN_DOOR_CLOSED_H1,
	ORANGE_DOOR_CLOSED_H1,
};

static const t_tile	g_hdoors2[] = {
	PURPLE_DOOR_CLOSED_H2,
	GREEN_DOOR_CLOSED_H2,
	ORANGE_DOOR_CLOSED_H2,
};

static const t_tile	g_vdoors[] = {
	PURPLE_DOOR_CLOSED,
	GREEN_DOOR_CLOSED,
	ORANGE_DOOR_CLOSED,
};

void	_scene_setup_door(t_scene *scene, t_ivec2 pos, t_uint tag)
{
	t_node	*node;
	t_node	*near[4];

	node = &scene->grid[pos.y][pos.x];
	scene_query_nearby(scene, pos, near);
	if (near[UP] && near[DOWN]
		&& is_tile_solid(near[UP]->tile) && is_tile_solid(near[DOWN]->tile))
	{
		node->tile = g_hdoors[tag];
		node->front_tile = g_hdoors2[tag];
	}
	else
		node->tile = g_vdoors[tag];
}

void	scene_key_pressed(t_scene *scene, t_game_data *game, int key)
{
	t_uint	keycode;
	t_key	key_val;

	keycode = (t_uint)key;
	key_val = 0;
	while (key_val < KEYCOUNT)
	{
		if (scene->keys.map[key_val] == keycode)
			break ;
		key_val++;
	}
	if (key_val < KEYCOUNT)
	{
		scene->keys.down[key_val] = TRUE;
		if (scene->player)
			player_key_press(scene->player, game, scene, key);
	}
}

void	scene_key_released(t_scene *scene, t_game_data *game, int key)
{
	t_uint	keycode;
	t_key	key_val;

	keycode = (t_uint)key;
	key_val = 0;
	while (key_val < KEYCOUNT)
	{
		if (scene->keys.map[key_val] == keycode)
			break ;
		key_val++;
	}
	if (key_val < KEYCOUNT)
	{
		scene->keys.down[key_val] = FALSE;
		if (scene->player)
			player_key_release(scene->player, game, scene, key);
	}
}
