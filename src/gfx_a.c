/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:46:08 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/10 15:46:09 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slgfx.h"
#include <stdlib.h>
#include "yvec2.h"
#include "slassets.h"
#include "mlx.h"
#include "ylist.h"
#include "slviewport.h"

t_gfx_context	*gfx_new_context(t_mlx_context *mlx, t_ivec2 ssize)
{
	t_gfx_context	*ctx;

	ctx = (t_gfx_context *)malloc(sizeof(t_gfx_context));
	ctx->scale = ivec2_new(1, 1);
	ctx->translation = ivec2_zero();
	ctx->display_surface = image_new(mlx, ssize);
	ctx->drawing_surface = image_new(mlx, ssize);
	ctx->views = list_new();
	return (ctx);
}

// Destroys graphics context
void	gfx_destroy_context(t_gfx_context *gfx, t_mlx_context *mlx)
{
	t_list_iter	i;

	image_destroy(gfx->display_surface, mlx);
	image_destroy(gfx->drawing_surface, mlx);
	i = list_iter(gfx->views);
	while (list_iter_next(&i))
		viewport_destroy((t_viewport *)i.value, mlx);
	list_delete(gfx->views);
	free(gfx);
}

void	gfx_draw_view(t_viewport *vp, t_gfx_context *gfx)
{
	image_draw_into(gfx->drawing_surface, vp->surface, vp->s_pos, vp->s_sca);
}

// Applies global scale to graphics context
void	gfx_scale(t_gfx_context *gfx, t_ivec2 sc)
{
	gfx->scale = sc;
}

// Blits graphics to screen
void	gfx_blit_to_screen(t_gfx_context *gfx, t_mlx_context *mlx)
{
	mlx_put_image_to_window(
		mlx->mlx,
		mlx->mlx_win,
		gfx->display_surface->img_ptr,
		0, 0);
}
