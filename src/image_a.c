/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:39:23 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/09 14:39:38 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slassets.h"
#include "yvec2.h"
#include "slmlx.h"
#include "mlx.h"
#include <stdlib.h>
#include "slxpm.h"

// Creates new (presumably empty) image
t_image	*image_new(t_mlxc *mlx, t_ivec2 size)
{
	t_image	*img;
	int		endian;

	if (size.x < 0 || size.y < 0)
		error_exit("Invalid image size");
	img = malloc(sizeof (t_image));
	img->img_ptr = mlx_new_image(mlx->mlx, size.x, size.y);
	img->pixel_data = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_length, &endian);
	img->big_endian = (t_bool)endian;
	img->size = size;
	img->origin = ivec2_zero();
	img->bpp_div_8 = img->bpp / 8;
	return (img);
}

// Destroys image data
void	image_destroy(t_image *img, t_mlxc *mlx)
{
	mlx_destroy_image(mlx->mlx, img->img_ptr);
	free(img);
}

// Loads image from file
t_image	*image_from_xpm_file(t_mlxc *mlx, const char *filepath)
{
	t_image	*img;
	t_ivec2	brush;
	t_argb	color;

	img = load_image_from_xpm((char *)filepath, mlx);
	brush.x = 0;
	while (brush.x < img->size.x)
	{
		brush.y = 0;
		while (brush.y < img->size.y)
		{
			color = image_get_pixel(img, brush.x, brush.y);
			if (color.r != 0 || color.g != 0 || color.b != 0)
				color.a = 255;
			else
				color.a = 0;
			image_set_pixel(img, brush.x, brush.y, color);
			brush.y++;
		}
		brush.x++;
	}
	return (img);
}
