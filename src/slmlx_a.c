/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slmlx_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:21:36 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/08 15:21:37 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slmlx.h"
#include "mlx.h"
#include <unistd.h>
#include "ycstr.h"
#include "yio.h"
#include "mlx.h"
#include <stdlib.h>

t_mlx_context	slmlx_context_new(t_ivec2 ws, char *title_name)
{
	t_mlx_context	ctx;

	if (ws.x < MIN_WIN_W && ws.y < MIN_WIN_H)
		error_exit("Invalid window size");
	ctx.mlx = mlx_init();
	ctx.mlx_win = mlx_new_window(ctx.mlx, ws.x, ws.y, title_name);
	return (ctx);
}

void	slmlx_context_destroy(t_mlx_context c)
{
	mlx_destroy_window(c.mlx, c.mlx_win);
}

void	error_exit(char *msg)
{
	char	*msg_nl;

	msg_nl = cstr_join(msg, "\n");
	write_cstr_fd(STDERR_FILENO, "Error\n");
	write_cstr_fd(STDERR_FILENO, msg_nl);
	free(msg_nl);
	exit(1);
}
