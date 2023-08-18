/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:29:24 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/09 13:29:25 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slassets.h"
#include "slgame.h"
#include "slmlx.h"
#include "mlx.h"
#include "yprint.h"
#include <stdlib.h>
#include "ydefines.h"
#include "slgfx.h"
#include "ystring.h"
#include "slgfx.h"
#include "slcolor.h"
#include "yvec2.h"
#include <time.h>
#include <stdio.h>
#include "slviewport.h"
#include <math.h>
#include "ylist.h"
#include "slviewport.h"
#include <math.h>
#include "ylist.h"
#include "slscene.h"
#include "sltga.h"

#define GAME_SCREEN_HEIGHT 288

static void	setup_hooks(t_game_data *game)
{
	mlx_loop_hook(game->mlx_ctx.mlx, game_update, game);
	mlx_hook(game->mlx_ctx.mlx_win, DESTROY_CODE, 0, game_destroy, game);
	mlx_hook(game->mlx_ctx.mlx_win, KEYDOWN_CODE, KEYDOWN_MASK,
		game_input_pressed, game);
	mlx_hook(game->mlx_ctx.mlx_win, KEYUP_CODE, KEYUP_MASK,
		game_input_released, game);
}

t_game_data	*game_new(const char *cfgp, const char *astp,
			const char *scene_path)
{
	t_game_data	*game;
	t_ivec2		vp_size;
	t_dvec2		vp_scale;
	t_viewport	*vp;

	game = (t_game_data *)malloc(sizeof(t_game_data));
	game->title = string_from_cstr("so sneaky!");
	game->config = load_game_config(cfgp, YNULL);
	yprintf("Loaded config\n");
	print_config(game->config);
	game->mlx_ctx = slmlx_context_new(game->config.window_size,
			game->title->cstr);
	game->gfx = gfx_new_context(&game->mlx_ctx, game->config.window_size);
	setup_hooks(game);
	(yprintf("Loading assets..."), game->assets = assets_new());
	assets_load_from_file(game->assets, &game->mlx_ctx, (char *)astp);
	yprintf(" finished!\nLoading level...");
	game->scene = scene_new((char *)scene_path, game);
	(yprintf(" finished!\n"), game->elapsed_time = clock());
	calc_resolution_scaling(game->config.window_size, GAME_SCREEN_HEIGHT,
		&vp_size, &vp_scale);
	vp = gfx_new_viewport(game->gfx, &game->mlx_ctx, vp_size);
	vp->s_sca = vp_scale;
	return (game);
}
	// yprintf("Viewport size: (%d, %d)\n", vp_size.x, vp_size.y);
	// printf("Viewport scale: (%f, %f)\n", vp_scale.x, vp_scale.y);

int	game_destroy(t_game_data *gd)
{
	yprintf("Exiting...\n");
	scene_delete(gd->scene);
	assets_delete(gd->assets, &gd->mlx_ctx);
	gfx_destroy_context(gd->gfx, &gd->mlx_ctx);
	slmlx_context_destroy(gd->mlx_ctx);
	string_delete(gd->title);
	free(gd);
	exit(0);
	return (0);
}
