/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:01:03 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/26 16:01:05 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slactor.h"
#include <stdlib.h>
#include <math.h>
#include "slscene_types.h"
#include "ylib.h"
#include "yvec2.h"
#include "slscene.h"

static const char	*g_item_names[ITEM_TYPE_COUNT] = {
	"None",
	"Purple Keycard",
	"Green Keycard",
	"Orange Keycard",
};

static void	player_collide(t_actor *player, t_scene *scene)
{
	t_item	item;
	t_tile	tile;

	item = scene->grid[player->position.y][player->position.x].item;
	tile = scene->grid[player->position.y][player->position.x].tile;
	if (is_pickup_item(item))
	{
		if (item == PURPLE_KEYCARD)
			scene->player_state.purple_keycard = TRUE;
		else if (item == GREEN_KEYCARD)
			scene->player_state.green_keycard = TRUE;
		else if (item == ORANGE_KEYCARD)
			scene->player_state.orange_keycard = TRUE;
		yprintf("Player picked up a %s\n", g_item_names[item]);
		scene->grid[player->position.y][player->position.x].item = NO_ITEM;
		scene_on_item_pickup(scene, item);
	}
	if (tile == EXIT)
		scene->update_status = EXIT_STATUS;
}

void	player_update(t_actor *player, t_game_data *game, t_scene *scene,
		double dt)
{
	t_ivec2		inp_dir;

	inp_dir.x = scene->keys.down[KEY_RIGHT] - scene->keys.down[KEY_LEFT];
	inp_dir.y = scene->keys.down[KEY_DOWN] - scene->keys.down[KEY_UP];
	player_move(player, scene, inp_dir);
	(void)scene;
	(void)dt;
	(void)game;
}

// You ever feel like this norm thing encourages playing coding golf more
// than writing simple and readable code?
void	player_try_open_door(t_scene *scene, t_direction dir,
		t_node *nodes[4])
{
	(void)!((scene->player_state.purple_keycard
		&& nodes[dir]->tile == PURPLE_DOOR_CLOSED)
		&& (nodes[dir]->tile = PURPLE_DOOR_OPEN));
	(void)!((scene->player_state.purple_keycard
		&& nodes[dir]->tile == PURPLE_DOOR_CLOSED_H1)
		&& (nodes[dir]->tile = PURPLE_DOOR_OPEN_H1,
			nodes[dir]->front_tile = PURPLE_DOOR_OPEN_H2));
	(void)!((scene->player_state.green_keycard
		&& nodes[dir]->tile == GREEN_DOOR_CLOSED)
		&& (nodes[dir]->tile = GREEN_DOOR_OPEN));
	(void)!((scene->player_state.green_keycard
		&& nodes[dir]->tile == GREEN_DOOR_CLOSED_H1)
		&& (nodes[dir]->tile = GREEN_DOOR_OPEN_H1,
			nodes[dir]->front_tile = GREEN_DOOR_OPEN_H2));
	(void)!((scene->player_state.orange_keycard
		&& nodes[dir]->tile == ORANGE_DOOR_CLOSED)
		&& (nodes[dir]->tile = ORANGE_DOOR_OPEN));
	(void)!((scene->player_state.orange_keycard
		&& nodes[dir]->tile == ORANGE_DOOR_CLOSED_H1)
		&& (nodes[dir]->tile = ORANGE_DOOR_OPEN_H1,
			nodes[dir]->front_tile = ORANGE_DOOR_OPEN_H2));
}

void	player_move(t_actor *player, t_scene *scene, t_ivec2 inp_dir)
{
	t_direction		dir;
	t_node			*node[4];
	t_move_result	result;

	if (ivec2_length_sq(inp_dir) == 0)
		return ;
	(void)!(inp_dir.x == 1 && (dir = RIGHT));
	(void)!(inp_dir.x == -1 && (dir = LEFT));
	(void)!(inp_dir.y == 1 && (dir = DOWN));
	(void)!(inp_dir.y == -1 && (dir = UP));
	scene_query_nearby(scene, player->position, node);
	result = actor_move(player, scene, dir);
	if (result == MOVE_SUCCESS)
	{
		scene->player_state.move_count++;
		player_collide(player, scene);
	}
	else if (result == HIT_SOLID)
		player_try_open_door(scene, dir, node);
	else if (result == HIT_ACTOR
		&& (node[dir]->actor->type == ENEMY
			|| node[dir]->actor->type == RAT))
		node[dir]->actor->direction = (dir + 2) % 4;
}
