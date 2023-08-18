/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patrol_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:13:42 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/06/06 13:13:44 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slactor.h"
#include "slscene.h"
#include "slscene_types.h"
#include "ylib.h"
#include "yvec2.h"

void	patrol_update(t_actor *enemy, t_game_data *game, t_scene *scene,
		double dt)
{
	(void)game;
	(void)dt;
	if (enemy->state == IDLE)
	{
		if (enemy->walk_strategy == RANDOM_WALK)
			actor_walk_randomly(enemy, scene);
		if (enemy->walk_strategy == HUG_WALL_WALK)
			actor_hug_wall(enemy, scene);
		if (enemy->walk_strategy == LAZY_TURNING_WALK)
			actor_lazy_turning(enemy, scene);
		if (actor_vision_test(scene, enemy, scene->player))
		{
			yprintf("Gotcha!\n");
			scene->camera_focus_actor = enemy;
			enemy->state = ACTION;
			enemy->draw_offset = ivec2_zero();
			scene->player->state = NEUTRALIZED;
			enemy->timer = 2.0;
		}
	}
	if (enemy->state == ACTION && enemy->timer <= 0.0)
		scene->update_status = FAIL_STATUS;
}
