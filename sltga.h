/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sltga.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:03:48 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/29 15:03:49 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLTGA_H
# define SLTGA_H

// Fuck minilibx. It segfaults when you try to load xpm image on linux, so I 
// had to make my own xpm loader. Turns out xpm has "special color symbols" -
// a load of various color names that you may encounter instead of color values
// when parsing xpm file, because fuck you dear developer. Fuck. You. So
// instead of implementing that collosal lookup table, I'm going to use tga 
// file format for images, and create my own tga image loader.

# include "slcolor.h"
# include "ytypes.h"
# include "slassets.h"
# include "slmlx.h"
# include "ytypes.h"

typedef struct s_tga_data {
	t_uchar	idlen;
	t_uchar	colormap_type;
	t_uchar	image_data_type;
	struct s_tga_image_header {
		short		origin_x;
		short		origin_y;
		t_ushort	width;
		t_ushort	height;
		t_uchar		pixel_depth;
		t_uchar		descriptor;
	}	image;
}	t_tga_data;

// Loads image from TGA file
t_image	*load_image_from_tga(char *path, t_mlx_context *mlx);

// (internal function) reads raw uncompressed TGA image data
void	_read_tga_data(int ifd, t_tga_data tga, t_image *img);

// (internal function) reads run-length encoded TGA image data
void	_read_rl_tga_data(int ifd, t_tga_data tga, t_image *img);

#endif
