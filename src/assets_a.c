/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:04:16 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/23 13:04:18 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slassets.h"
#include <unistd.h>
#include "ycstr.h"
#include "yio.h"
#include "ystring.h"
#include "ylist.h"
#include <stdlib.h>
#include "ydefines.h"

t_asset_col	*assets_new(void)
{
	t_asset_col	*col;
	t_uint		i;

	col = (t_asset_col *)malloc(sizeof(t_asset_col));
	i = 0;
	while (i < ASSET_TYPE_COUNT)
	{
		col->assets[i] = list_new();
		i++;
	}
	return (col);
}

static void	delete_image_asset(t_asset *asset, t_mlxc *mlxc)
{
	image_destroy(asset->asset, mlxc);
	string_delete(asset->name);
	free(asset);
}

static void	delete_text_asset(t_asset *asset)
{
	string_delete(asset->asset);
	string_delete(asset->name);
	free(asset);
}

void	assets_delete(t_asset_col *col, t_mlxc *mlxc)
{
	list_capply(col->assets[IMAGE_ASSET],
		(t_capply_func)delete_image_asset, mlxc);
	list_delete(col->assets[IMAGE_ASSET]);
	list_apply(col->assets[TEXT_ASSET], (t_apply_func)delete_text_asset);
	list_delete(col->assets[TEXT_ASSET]);
	free(col);
}
