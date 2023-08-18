/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slgame.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:32:05 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/08 14:32:06 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLGAME_H
# define SLGAME_H
# include "ytypes.h"
# include "slmlx.h"
# include "slcolor.h"
# include "slgfx.h"
# include "yvec2.h"
# include "slassets.h"
# include "slscene_types.h"
# include <time.h>

// Game config
typedef struct s_game_config {
	t_ivec2	window_size;
	t_uint	up_keycode;
	t_uint	down_keycode;
	t_uint	left_keycode;
	t_uint	right_keycode;
	t_uint	action_keycode;
	t_uint	cancel_keycode;
	t_uint	quit_keycode;
	t_uint	debug_keycode;
}	t_game_config;

// Loads game config from specified filepath. line_cstr should be NULL
t_game_config	load_game_config(const char *filepath, char *line_cstr);

// Prints config to stdout
void			print_config(t_game_config c);

struct	s_scene;

// Game data structure
typedef struct s_game_data {
	t_string		*title;
	t_mlx_context	mlx_ctx;
	struct s_scene	*scene;
	t_game_config	config;
	t_asset_col		*assets;
	t_gfx_context	*gfx;
	clock_t			elapsed_time;
}	t_game_data;

t_game_data		*game_new(const char *cfgp, const char *astp,
					const char *scene_path);
int				game_update(t_game_data *gd);
void			game_draw(t_game_data *gd);
int				game_input_pressed(int key, t_game_data *gd);
int				game_input_released(int key, t_game_data *gd);
int				game_destroy(t_game_data *gd);
void			calc_resolution_scaling(t_ivec2 window_size,
					int target_height,
					t_ivec2 *out_size, t_dvec2 *out_scale);

#endif
