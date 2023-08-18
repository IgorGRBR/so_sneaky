/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:04:01 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/29 15:04:02 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slmlx.h"
#include "sltga.h"
#include "slassets.h"
#include "ylib.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static t_tga_data	parse_header(int ifd)
{
	t_tga_data	tga;
	t_bool		success;
	char		dummy[5];

	success = read(ifd, &tga.idlen, 1) == 1;
	success *= read(ifd, &tga.colormap_type, 1) == 1;
	success *= read(ifd, &tga.image_data_type, 1) == 1;
	success *= read(ifd, dummy, 5) == 5;
	success *= read(ifd, &tga.image, 10) == 10;
	if (!success)
		error_exit("TGA header reading error");
	if (tga.colormap_type != 0 || (tga.image_data_type != 2
			&& tga.image_data_type != 10))
		error_exit("TGA loader only supports"
			" uncompressed or run-length encoded truecolor images"
			"  without colormap");
	return (tga);
}

t_image	*load_image_from_tga(char *path, t_mlx_context *mlx)
{
	t_image		*img;
	t_tga_data	tga;
	int			ifd;

	if (!try_open_file_cstr((const char *)path, O_RDONLY, &ifd))
		error_exit("Can't open/read tga file");
	tga = parse_header(ifd);
	img = image_new(mlx, ivec2_new(tga.image.width, tga.image.height));
	img->origin = ivec2_new(tga.image.origin_x, tga.image.origin_y);
	if (tga.image_data_type == 2)
		_read_tga_data(ifd, tga, img);
	else if (tga.image_data_type == 10)
		_read_rl_tga_data(ifd, tga, img);
	close(ifd);
	return (img);
}
