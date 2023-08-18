/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:47:03 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/06/09 13:47:04 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slactor.h"
#include "slscene.h"
#include <stdlib.h>

static const t_direction	g_moves[9] = {
	UP,
	UP,
	UP,
	UP,
	RIGHT,
	RIGHT,
	LEFT,
	LEFT,
	DOWN,
};

void	actor_walk_randomly(t_actor *actor, t_scene *scene)
{
	t_uint			choice;
	t_uint			attempt;
	t_direction		dir;
	t_node			*node[4];
	t_move_result	result;

	attempt = 0;
	scene_query_nearby(scene, actor->position, node);
	while (attempt < 10)
	{
		choice = random() % 9;
		dir = (actor->direction + g_moves[choice]) % 4;
		result = actor_move(actor, scene, dir);
		if (result == MOVE_SUCCESS || (result == HIT_ACTOR
				&& node[actor->direction]->actor->type == PLAYER))
			return ;
		attempt++;
	}
}

void	actor_hug_wall(t_actor *actor, t_scene *scene)
{
	int				attempt;
	t_direction		dir;
	t_node			*near[4];
	t_move_result	result;

	(scene_query_nearby(scene, actor->position, near), attempt = -1);
	while (++attempt < 4)
	{
		dir = (actor->direction + actor->turn_preference) % 4;
		(void)!(!is_tile_solid(near[dir]->tile)
			&& (actor->direction += ((actor->turn_preference == RIGHT)
				- (actor->turn_preference == LEFT)), actor->direction %= 4));
		result = actor_move(actor, scene, actor->direction);
		if (result == MOVE_SUCCESS || (result == HIT_ACTOR
				&& near[actor->direction]->actor->type == PLAYER))
			return ;
		else if (result == HIT_SOLID)
		{
			actor->direction -= ((actor->turn_preference == RIGHT)
					- (actor->turn_preference == LEFT));
			actor->direction %= 4;
		}
	}
}

void	actor_lazy_turning(t_actor *actor, t_scene *scene)
{
	t_direction		dir;
	t_node			*near[4];
	t_move_result	result;

	(scene_query_nearby(scene, actor->position, near), dir = actor->direction);
	if (is_tile_solid(near[dir]->tile))
		dir = (actor->direction + actor->turn_preference) % 4;
	if (is_tile_solid(near[dir]->tile))
		dir = (actor->direction + actor->turn_preference + 2) % 4;
	if (is_tile_solid(near[dir]->tile))
		dir = (actor->direction + 2) % 4;
	if (is_tile_solid(near[dir]->tile))
		dir = (actor->direction + actor->turn_preference + 1) % 4;
	result = actor_move(actor, scene, dir);
	if (result == MOVE_SUCCESS)
		return ;
}
