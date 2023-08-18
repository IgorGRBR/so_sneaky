/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slactor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:46:45 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/25 14:46:46 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLACTOR_H
# define SLACTOR_H
# include "slgame.h"
# include "slscene_types.h"
# include "slviewport.h"
# include "ytypes.h"

// In seconds
# define ACTOR_MOVE_TIME 0.5

t_actor			*actor_new(t_ivec2 position, t_direction direction,
					t_actor_type type);
void			actor_delete(t_actor *actor);

void			actor_draw(t_actor *a, t_viewport *vp, t_scene *scene);

void			actor_update(t_actor *actor, t_game_data *game, double dt);

typedef enum e_move_result {
	MOVE_FAIL,
	MOVE_SUCCESS,
	HIT_SOLID,
	HIT_ACTOR,
}	t_move_result;

t_move_result	actor_move(t_actor *actor, t_scene *scene, t_direction dir);

// Checks if actor a can see actor b
t_bool			actor_vision_test(t_scene *scene, t_actor *a, t_actor *b);

// Actor walking strategies
void			actor_walk_randomly(t_actor *actor, t_scene *scene);

void			actor_hug_wall(t_actor *actor, t_scene *scene);

void			actor_lazy_turning(t_actor *actor, t_scene *scene);

// Actor type-specific update functions
void			player_update(t_actor *player, t_game_data *game,
					t_scene *scene, double dt);

void			player_key_press(t_actor *player, t_game_data *game,
					t_scene *scene, int key);

void			player_key_release(t_actor *player, t_game_data *game,
					t_scene *scene, int key);

void			player_move(t_actor *player, t_scene *scene, t_ivec2 inp_dir);

void			patrol_update(t_actor *enemy, t_game_data *game,
					t_scene *scene, double dt);

void			rat_update(t_actor *rat, t_game_data *game, t_scene *scene,
					double dt);

#endif
