/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:18:48 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/30 14:18:49 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slactor.h"
#include <stdlib.h>
#include <math.h>
#include "ylib.h"

void	player_key_press(t_actor *player, t_game_data *game, t_scene *scene,
		int key)
{
	t_uint		keycode;
	t_bool		moving;
	t_ivec2		inp_dir;

	keycode = (t_uint)key;
	moving = TRUE;
	inp_dir = ivec2_zero();
	if (keycode == game->config.left_keycode)
		inp_dir.x = -1;
	else if (keycode == game->config.right_keycode)
		inp_dir.x = 1;
	else if (keycode == game->config.up_keycode)
		inp_dir.y = -1;
	else if (keycode == game->config.down_keycode)
		inp_dir.y = 1;
	else
		moving = FALSE;
	if (moving)
		player_move(player, scene, inp_dir);
}

void	player_key_release(t_actor *player, t_game_data *game, t_scene *scene,
		int key)
{
	(void)player;
	(void)game;
	(void)scene;
	(void)key;
}
