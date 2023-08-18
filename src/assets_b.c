/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:26:07 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/23 13:26:10 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slassets.h"
#include <unistd.h>
#include "ycstr.h"
#include "ystring.h"
#include "ylist.h"
#include <stdlib.h>
#include "ydefines.h"
#include <fcntl.h>
#include "yio.h"
#include "yprint.h"
#include "sltga.h"

t_asset	*assets_get_asset(t_asset_col *col, char *name,
	enum e_asset_type type)
{
	t_string	*name_str;
	t_list_iter	it;
	t_asset		*asset;

	name_str = string_from_cstr(name);
	it = list_iter(col->assets[type]);
	while (list_iter_next(&it))
	{
		asset = (t_asset *)it.value;
		if (string_compare(name_str, asset->name) == 0)
		{
			string_delete(name_str);
			return (asset);
		}
	}
	string_delete(name_str);
	return (YNULL);
}

t_bool	assets_load_image_xpm(t_asset_col *col, t_mlxc *mlx, char *name,
		char *path)
{
	t_image		*img;
	t_string	*path_str;
	int			ifd;
	t_asset		*asset;

	path_str = string_from_cstr(path);
	if (!try_open_file(path_str, O_RDONLY, &ifd))
		return (string_delete(path_str), FALSE);
	(close(ifd), string_delete(path_str));
	img = image_from_xpm_file(mlx, (const char *)path);
	asset = assets_get_asset(col, name, IMAGE_ASSET);
	if (asset)
	{
		yprintf("Reloading image %s\n", name);
		free(asset->name);
		image_destroy(asset->asset, mlx);
	}
	else
	{
		asset = (t_asset *)malloc(sizeof(t_asset));
		list_insert(col->assets[IMAGE_ASSET], asset);
	}
	asset->name = string_from_cstr(name);
	asset->asset = img;
	return (TRUE);
}

t_bool	assets_load_text(t_asset_col *col, char *name, char *path)
{
	t_list		*lines;
	t_string	*content;
	t_asset		*asset;

	lines = read_file_to_lines_cstr(path, O_RDONLY);
	if (!lines)
		return (FALSE);
	content = string_new();
	list_capply(lines, (t_capply_func)string_append2, content);
	list_apply(lines, (t_apply_func)string_delete);
	list_delete(lines);
	asset = assets_get_asset(col, name, TEXT_ASSET);
	if (asset)
	{
		yprintf("Reloading text %s\n", name);
		string_delete(asset->asset);
	}
	else
	{
		asset = (t_asset *)malloc(sizeof(t_asset));
		asset->name = string_from_cstr(name);
		list_insert(col->assets[TEXT_ASSET], asset);
	}
	asset->asset = content;
	return (TRUE);
}

t_bool	assets_load_image_tga(t_asset_col *col, t_mlxc *mlx, char *name,
		char *path)
{
	t_image		*img;
	t_string	*path_str;
	int			ifd;
	t_asset		*asset;

	path_str = string_from_cstr(path);
	if (!try_open_file(path_str, O_RDONLY, &ifd))
		return (string_delete(path_str), FALSE);
	(close(ifd), string_delete(path_str));
	img = load_image_from_tga(path, mlx);
	asset = assets_get_asset(col, name, IMAGE_ASSET);
	if (asset)
	{
		yprintf("Reloading image %s\n", name);
		free(asset->name);
		image_destroy(asset->asset, mlx);
	}
	else
	{
		asset = (t_asset *)malloc(sizeof(t_asset));
		list_insert(col->assets[IMAGE_ASSET], asset);
	}
	asset->name = string_from_cstr(name);
	asset->asset = img;
	return (TRUE);
}
