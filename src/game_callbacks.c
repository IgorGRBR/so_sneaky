/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_callbacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:52:31 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/25 14:52:32 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slgame.h"
#include "slviewport.h"
#include "ylist.h"
#include "slgfx.h"
#include "slscene.h"
#include "mlx.h"
#include "slmlx.h"
#include <stdlib.h>
#include "yprint.h"
#include "ystring.h"
#include "ycstr.h"

#include <stdio.h>

static void	draw_move_count(t_game_data *game)
{
	char	*count_cstr;

	mlx_string_put(game->mlx_ctx.mlx, game->mlx_ctx.mlx_win,
		0, 96,
		0xFFFF0000, "Moves: ");
	count_cstr = cstr_itoa(game->scene->player_state.move_count);
	mlx_string_put(game->mlx_ctx.mlx, game->mlx_ctx.mlx_win,
		128, 96,
		0xFFFF0000, count_cstr);
	free(count_cstr);
}

static void	draw_the_game(t_game_data *game)
{
	t_viewport		*vp;

	gfx_clear_surface(game->gfx, argb_new(0, 0, 0, 0));
	vp = list_get(game->gfx->views, 0);
	if (vp)
	{
		viewport_clear(vp, argb_new(0, 0, 0, 0));
		scene_draw(game->scene, vp);
	}
	list_capply(game->gfx->views, (t_capply_func)gfx_draw_view, game->gfx);
	gfx_swap_surface(game->gfx);
	gfx_blit_to_screen(game->gfx, &game->mlx_ctx);
	draw_move_count(game);
}

int	game_update(t_game_data *gd)
{
	double			delta_time;
	t_update_status	status;

	delta_time = ((double)clock() - gd->elapsed_time) / CLOCKS_PER_SEC;
	gd->elapsed_time = clock();
	status = scene_update(gd->scene, delta_time, gd);
	(void)(status == EXIT_STATUS && yprintf("Player reached the exit!\n"));
	(void)(status == FAIL_STATUS && yprintf("Player has failed!\n"));
	if (status != CONTINUE_STATUS)
	{
		yprintf("Final move count: %d\n", gd->scene->player_state.move_count);
		game_destroy(gd);
	}
	draw_the_game(gd);
	return (1);
}
// Insert the following at the end of the previous function to debug draw times
	// char dt_str[32];
	// sprintf(dt_str, "dt: %f", delta_time);
	// mlx_string_put(gd->mlx_ctx.mlx, gd->mlx_ctx.mlx_win,
	// 	0, 64,
	// 	0xFFFF0000, dt_str);

int	game_input_pressed(int key, t_game_data *gd)
{
	t_uint		keycode;
	t_list_iter	it;
	t_asset		*asset;

	keycode = (t_uint)key;
	it = list_iter(gd->assets->assets[IMAGE_ASSET]);
	if (keycode == gd->config.quit_keycode)
		game_destroy(gd);
	if (gd->scene)
		scene_key_pressed(gd->scene, gd, key);
	if (keycode == gd->config.debug_keycode)
	{
		yprintf("loaded sprites:\n");
		while (list_iter_next(&it))
		{
			asset = it.value;
			yprintf("\t%s: %p\n", asset->name->cstr, asset->asset);
		}
	}
	return (0);
}

int	game_input_released(int key, t_game_data *gd)
{
	if (gd->scene)
		scene_key_released(gd->scene, gd, key);
	return (0);
}
