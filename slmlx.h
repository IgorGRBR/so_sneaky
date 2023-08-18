/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slmlx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:43:25 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/04 12:43:26 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLMLX_H
# define SLMLX_H
# include "ytypes.h"

# define MIN_WIN_W 320
# define MIN_WIN_H 240

// Events
enum e_mlx_event {
	KEYDOWN_CODE = 2,
	KEYUP_CODE = 3,
	MOUSEDOWN_CODE = 4,
	MOUSEUP_CODE = 5,
	MOUSEMOVE_CODE = 6,
	EXPOSE_CODE = 12,
	DESTROY_CODE = 17,
};

enum e_mlx_event_mask {
	KEYDOWN_MASK = 1L<<0,
	KEYUP_MASK = 1L<<1,
	MOUSEDOWN_MASK = 1L<<2,
	MOUSEUP_MASK = 1L<<3,
	MOUSEMOVE_MASK = 1L<<6,
	EXPOSE_MASK = 1L<<15,
};

// MiniLibX context
typedef struct s_mlx_context {
	void	*mlx;
	void	*mlx_win;
}	t_mlx_context;

// Shorthand for t_mlx_context
typedef t_mlx_context	t_mlxc;

// Initializes mlx context with specified window size
t_mlx_context	slmlx_context_new(t_ivec2 ws, char *title_name);

// Destroys mlx context
void			slmlx_context_destroy(t_mlx_context c);

// Prints message to stderr and exits
void			error_exit(char *msg);

#endif
