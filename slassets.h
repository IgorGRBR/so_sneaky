/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slassets.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:01:19 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/09 14:01:21 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLASSETS_H
# define SLASSETS_H
# include "ytypes.h"
# include "slcolor.h"
# include "slmlx.h"

typedef enum e_asset_type {
	IMAGE_ASSET,
	TEXT_ASSET,
	ASSET_TYPE_COUNT,
}	t_asset_type;

typedef struct s_asset_col {
	t_list		*assets[ASSET_TYPE_COUNT];
}	t_asset_col;

typedef struct s_asset {
	t_string		*name;
	void			*asset;
}	t_asset;

typedef struct s_image {
	void	*img_ptr;
	char	*pixel_data;
	int		bpp;
	int		bpp_div_8;
	int		line_length;
	t_bool	big_endian;
	t_ivec2	size;
	t_ivec2	origin;
}	t_image;

// Creates new (presumably empty) image
t_image		*image_new(t_mlxc *mlx, t_ivec2 size);

// Destroys image data
void		image_destroy(t_image *img, t_mlxc *mlx);

// Sets the pixel in image
void		image_set_pixel(t_image *img, int x, int y, t_argb color);

// Returns pixel color from the image
t_argb		image_get_pixel(t_image *img, int x, int y);

// Loads image from file
t_image		*image_from_xpm_file(t_mlxc *mlx, const char *filepath);

// Draws another image to the given image buffer
t_bool		image_draw_into(t_image *img, t_image *img2, t_ivec2 pos,
				t_dvec2 sc);

// Create a new asset collection
t_asset_col	*assets_new(void);

// Delete asset collection
void		assets_delete(t_asset_col *col, t_mlxc *mlxc);

// Loads image from xpm file into the assets list
t_bool		assets_load_image_xpm(t_asset_col *col, t_mlxc *mlx, char *name,
				char *path);

// Loads image from tga file into assets list
t_bool		assets_load_image_tga(t_asset_col *col, t_mlxc *mlx, char *name,
				char *path);

// Loads txt file contents into the assets list
t_bool		assets_load_text(t_asset_col *col, char *name,
				char *path);

// Generic asset retrieval (internal use only)
t_asset		*assets_get_asset(t_asset_col *col, char *name,
				enum e_asset_type type);

// Retrieve an image from asset list (or NULL if it doesn't exist)
t_image		*assets_get_image(t_asset_col *col, char *name);

// Retrieve an text from asset list (or NULL if it doesn't exist)
t_string	*assets_get_text(t_asset_col *col, char *name);

// Load/update asset collection from file
void		assets_load_from_file(t_asset_col *col, t_mlxc *mlxc, char *path);

#endif
