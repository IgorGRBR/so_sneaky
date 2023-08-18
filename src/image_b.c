/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:47:34 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/10 13:47:35 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slassets.h"
#include "yvec2.h"
#include "slmlx.h"
#include "mlx.h"
#include "ymath.h"
#include <math.h>
#include "slutils.h"
#include "slcolor.h"
#include "yprint.h"

static t_argb	sample_color(t_image *img, t_dvec2 s_pos)
{
	t_ivec2	texture_pos;

	s_pos.x = s_pos.x - (long)s_pos.x;
	if (s_pos.x < 0.0)
		s_pos.x += 1.0;
	s_pos.y = s_pos.y - (long)s_pos.y;
	if (s_pos.y < 0.0)
		s_pos.y += 1.0;
	texture_pos.x = int_clamp((int)round((double)img->size.x * s_pos.x), 0,
			img->size.x - 1);
	texture_pos.y = int_clamp((int)round((double)img->size.y * s_pos.y), 0,
			img->size.y - 1);
	return (image_get_pixel(img, texture_pos.x, texture_pos.y));
}

// primitive blending
static t_argb	blend_colors(t_argb a, t_argb b)
{
	if (b.a == 0)
		return (a);
	return (b);
}

static void	paint_image(t_image *im, t_image *im2, t_ivec2 pts[2], t_ivec2 pd)
{
	t_ivec2	brush;
	t_dvec2	s_pos;
	t_ivec2	size;
	t_argb	color;
	t_ivec2	lpts[2];

	size = ivec2_sub(pts[1], pts[0]);
	lpts[0] = ivec2_new(int_max(pts[0].x, 0), int_max(pts[0].y, 0));
	brush = lpts[0];
	lpts[1].x = int_min(pts[1].x, im->size.x);
	lpts[1].y = int_min(pts[1].y, im->size.y);
	while (brush.y < lpts[1].y)
	{
		brush.x = lpts[0].x;
		while (brush.x < lpts[1].x)
		{
			color = image_get_pixel(im, brush.x, brush.y);
			s_pos.x = (double)(brush.x - pts[0].x) / (double)(size.x * pd.x);
			s_pos.y = (double)(brush.y - pts[0].y) / (double)(size.y * pd.y);
			image_set_pixel(im, brush.x, brush.y,
				blend_colors(color, sample_color(im2, s_pos)));
			brush.x++;
		}
		brush.y++;
	}
}

t_bool	image_draw_into(t_image *img, t_image *img2, t_ivec2 pos, t_dvec2 sc)
{
	t_ivec2	pts[2];
	t_ivec2	tf_tl;
	t_ivec2	tf_br;
	t_ivec2	p_dir;

	tf_tl.x = pos.x + trunc(-img2->origin.x * sc.x);
	tf_tl.y = pos.y + trunc(-img2->origin.y * sc.y);
	tf_br.x = pos.x + trunc((img2->size.x - img2->origin.x) * sc.x);
	tf_br.y = pos.y + trunc((img2->size.y - img2->origin.y) * sc.y);
	pts[0].x = int_min(tf_tl.x, tf_br.x);
	pts[0].y = int_min(tf_tl.y, tf_br.y);
	pts[1].x = int_max(tf_tl.x, tf_br.x);
	pts[1].y = int_max(tf_tl.y, tf_br.y);
	p_dir = ivec2_new((sc.x > 0) * 2 - 1, (sc.y > 0) * 2 - 1);
	if (iaabb_test(ivec2_zero(), img->size, pts[0], ivec2_sub(pts[1], pts[0])))
	{
		paint_image(img, img2, pts, p_dir);
		return (TRUE);
	}
	return (FALSE);
}
