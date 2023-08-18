/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:56:49 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/10 15:56:50 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slgfx.h"
#include <stdlib.h>
#include "yvec2.h"
#include "slassets.h"
#include "mlx.h"
#include "slviewport.h"
#include "ylist.h"

// Clear context surface with color
void	gfx_clear_surface(t_gfx_context *gfx, t_argb color)
{
	t_ivec2	brush;

	brush = ivec2_zero();
	color.a = 255;
	while (brush.y < gfx->drawing_surface->size.y)
	{
		brush.x = 0;
		while (brush.x < gfx->drawing_surface->size.x)
		{
			image_set_pixel(gfx->drawing_surface,
				brush.x, brush.y, color);
			brush.x++;
		}
		brush.y++;
	}
}

// Swap active and drawn surfaces
void	gfx_swap_surface(t_gfx_context *gfx)
{
	t_image	*temp;

	temp = gfx->display_surface;
	gfx->display_surface = gfx->drawing_surface;
	gfx->drawing_surface = temp;
}

t_viewport	*gfx_new_viewport(t_gfx_context *gfx, t_mlxc *c, t_ivec2 s)
{
	t_viewport	*vp;

	vp = viewport_new(c, s);
	list_insert(gfx->views, vp);
	return (vp);
}
