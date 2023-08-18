/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:25:33 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/22 13:25:34 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slassets.h"
#include "slcolor.h"

// Sets the pixel in image
#ifdef VARYING_ENDIAN_IMAGES

void	image_set_pixel(t_image *img, int x, int y, t_argb color)
{
	char	*px_ptr;

	x = x % img->size.x;
	y = y % img->size.y;
	px_ptr = img->pixel_data;
	px_ptr += y * img->line_length;
	px_ptr += x * (img->bpp / 8);
	color.a = 255 - color.a;
	if (!img->big_endian)
		*(t_argb *)px_ptr = color;
	else
	{
		px_ptr[3] = color.a;
		px_ptr[2] = color.r;
		px_ptr[1] = color.g;
		px_ptr[0] = color.b;
	}
}
#else

void	image_set_pixel(t_image *img, int x, int y, t_argb color)
{
	char	*px_ptr;

	x = x % img->size.x;
	y = y % img->size.y;
	px_ptr = img->pixel_data + y * img->line_length + x * (img->bpp / 8);
	color.a = 255 - color.a;
	*(t_argb *)px_ptr = color;
}
#endif

// Returns pixel color from the image
#ifdef VARYING_ENDIAN_IMAGES

t_argb	image_get_pixel(t_image *img, int x, int y)
{
	char	*px_ptr;
	t_argb	color;

	x = x % img->size.x;
	y = y % img->size.y;
	px_ptr = img->pixel_data;
	px_ptr += y * img->line_length;
	px_ptr += x * (img->bpp / 8);
	if (!img->big_endian)
		color = *(t_argb *)px_ptr;
	else
	{
		color.a = 255 - *(t_uchar *)(px_ptr + 3);
		color.r = *(t_uchar *)(px_ptr + 2);
		color.g = *(t_uchar *)(px_ptr + 1);
		color.b = *(t_uchar *)(px_ptr);
	}
	return (color);
}
#else

t_argb	image_get_pixel(t_image *img, int x, int y)
{
	char	*px_ptr;
	t_argb	color;

	x = x % img->size.x;
	y = y % img->size.y;
	px_ptr = img->pixel_data + y * img->line_length + x * (img->bpp / 8);
	color = *(t_argb *)px_ptr;
	color.a = 255 - color.a;
	return (color);
}
#endif
