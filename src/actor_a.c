/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:15:52 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/25 15:15:53 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slscene.h"
#include "slactor.h"
#include <stdlib.h>
#include <math.h>
#include "ylib.h"

t_actor	*actor_new(t_ivec2 position, t_direction direction,
		t_actor_type type)
{
	t_actor	*actor;

	actor = (t_actor *)malloc(sizeof(t_actor));
	actor->direction = direction;
	actor->type = type;
	actor->image = YNULL;
	actor->draw_offset = ivec2_zero();
	actor->draw_frame = 0.0;
	actor->state = IDLE;
	actor->position = position;
	actor->timer = 0.0;
	actor->walk_strategy = RANDOM_WALK;
	actor->turn_preference = DOWN;
	return (actor);
}

void	actor_delete(t_actor *actor)
{
	free(actor);
}

static const t_ivec2	g_actor_dir[4] = {
{.x = 0, .y = -1},
{.x = 1, .y = 0},
{.x = 0, .y = 1},
{.x = -1, .y = 0},
};

void	actor_update(t_actor *actor, t_game_data *game, double dt)
{
	(void)game;
	if (actor->timer > 0.0)
	{
		actor->timer -= dt;
		if (actor->state == WALKING)
		{
			actor->draw_offset = ivec2_negate(
					ivec2_scale(g_actor_dir[actor->direction],
						(int)floor((32.0 / ACTOR_MOVE_TIME) * actor->timer)));
		}
	}
	if (actor->timer <= 0.0)
	{
		actor->draw_offset = ivec2_zero();
		actor->timer = 0.0;
		if (actor->state == WALKING)
			actor->state = IDLE;
	}
}

static t_bool	actor_try_move(t_actor *actor, t_scene *scene, t_direction dir)
{
	t_ivec2	next_pos;

	next_pos = ivec2_add(actor->position, g_actor_dir[dir]);
	if (!is_tile_solid(scene->grid[next_pos.y][next_pos.x].tile)
		&& scene->grid[next_pos.y][next_pos.x].actor == YNULL)
	{
		scene->grid[actor->position.y][actor->position.x].actor = YNULL;
		scene->grid[next_pos.y][next_pos.x].actor = actor;
		actor->position = next_pos;
		return (TRUE);
	}
	return (FALSE);
}

t_move_result	actor_move(t_actor *actor, t_scene *scene, t_direction dir)
{
	t_ivec2	fpos;

	fpos = ivec2_add(actor->position, g_actor_dir[dir]);
	if ((actor->timer <= 0.0 && actor->state == WALKING)
		|| actor->state == IDLE)
	{
		actor->direction = dir;
		if (actor_try_move(actor, scene, dir))
		{
			actor->state = WALKING;
			actor->timer = ACTOR_MOVE_TIME;
			actor->draw_offset = ivec2_negate(
					ivec2_scale(g_actor_dir[actor->direction],
						(int)floor((32.0 / ACTOR_MOVE_TIME) * actor->timer)));
			return (MOVE_SUCCESS);
		}
		else if (scene->grid[fpos.y][fpos.x].actor)
			return (HIT_ACTOR);
		return (HIT_SOLID);
	}
	return (MOVE_FAIL);
}
