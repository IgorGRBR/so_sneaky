/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:02:22 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/15 15:02:23 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slviewport.h"
#include "yvec2.h"
#include "slassets.h"
#include <stdlib.h>

t_viewport	*viewport_new(t_mlx_context *mlx, t_ivec2 ssize)
{
	t_viewport	*vp;

	vp = (t_viewport *)malloc(sizeof(t_viewport));
	vp->surface = image_new(mlx, ssize);
	vp->s_pos = ivec2_zero();
	vp->s_sca = dvec2_new(1.0, 1.0);
	vp->t_pos = ivec2_zero();
	vp->t_sca = dvec2_new(1.0, 1.0);
	return (vp);
}

void	viewport_destroy(t_viewport *vp, t_mlx_context *mlx)
{
	image_destroy(vp->surface, mlx);
	free(vp);
}

void	viewport_draw_image(t_viewport *vp,
	t_image *img, t_ivec2 pos, t_dvec2 sca)
{
	sca.x *= vp->t_sca.x;
	sca.y *= vp->t_sca.y;
	image_draw_into(vp->surface, img, ivec2_sub(pos, vp->t_pos), sca);
}

void	viewport_clear(t_viewport *vp, t_argb color)
{
	t_ivec2	brush;

	brush = ivec2_zero();
	color.a = 255;
	while (brush.y < vp->surface->size.y)
	{
		brush.x = 0;
		while (brush.x < vp->surface->size.x)
		{
			image_set_pixel(vp->surface,
				brush.x, brush.y, color);
			brush.x++;
		}
		brush.y++;
	}
}
