/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:58:34 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/06/01 13:58:35 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sltga.h"
#include "ylib.h"
#include "slassets.h"
#include <unistd.h>

// TODO: maybe i shouldnt ignore colormap field in the header
static void	skip_unused(int ifd, t_tga_data tga)
{
	char	dummy[256];
	t_bool	success;

	success = TRUE;
	if (tga.idlen > 0)
		success *= read(ifd, dummy, tga.idlen) == tga.idlen;
	if (!success)
		error_exit("TGA error when skipping unused data");
}

static void	set_pixel(t_image *image, t_ivec2 coord, t_ivec2 inv,
		t_uchar color_data[4])
{
	coord.y = image->size.y - coord.y - 1;
	if (inv.x)
		coord.x = image->size.x - coord.x - 1;
	if (inv.y)
		coord.y = image->size.y - coord.y - 1;
	image_set_pixel(image, coord.x, coord.y, *(t_argb *)color_data);
}

void	_read_tga_data(int ifd, t_tga_data tga, t_image *img)
{
	t_ivec2	a;
	t_ivec2	inverse;
	t_uchar	color[4];

	skip_unused(ifd, tga);
	inverse.x = tga.image.descriptor >> 4 & 1;
	inverse.y = tga.image.descriptor >> 5 & 1;
	a = ivec2_zero();
	while (a.y < tga.image.height)
	{
		a.x = 0;
		while (a.x < tga.image.width)
		{
			if (read(ifd, color, 4) != 4)
				error_exit("Error while reading TGA image data");
			set_pixel(img, a, inverse, color);
			a.x++;
		}
		a.y++;
	}
}

// This function is absolutely awful
void	_read_rl_tga_data(int ifd, t_tga_data tga, t_image *img)
{
	t_ivec2	a;
	t_ivec2	inverse;
	t_uchar	i;
	t_uchar	color[4];
	t_bool	raw;

	(skip_unused(ifd, tga), i = 1, raw = FALSE, a = ivec2_new(-1, -1));
	inverse.x = tga.image.descriptor >> 4 & 1;
	inverse.y = tga.image.descriptor >> 5 & 1;
	while (++a.y < tga.image.height)
	{
		a.x = -1;
		while (++a.x < tga.image.width)
		{
			if (--i == 0)
			{
				((void) !read(ifd, &i, 1), raw = i <= 127);
				i += 1 - 128 * !raw;
				(void) (!raw && read(ifd, color, 4) != 4);
			}
			(void)(raw && read(ifd, color, 4));
			set_pixel(img, a, inverse, color);
		}
	}
}
