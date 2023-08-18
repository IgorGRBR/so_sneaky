/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:43:25 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/04 12:43:26 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H
# include "slcolor.h"

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

// MiniLibX context
typedef struct s_mlx_context {
	void *mlx;
	void *mlx_win;
}	t_mlx_context;

t_mlx_context	slmlx_context_new(void);
void			slmlx_context_destroy(t_mlx_context c);
void			error_exit(char *msg);

#endif
