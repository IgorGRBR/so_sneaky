/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:12:44 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/29 16:12:45 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slassets.h"
#include "ydefines.h"

// Retrieve an image from asset list (or NULL if it doesn't exist)
t_image	*assets_get_image(t_asset_col *col, char *name)
{
	t_asset	*asset;

	asset = assets_get_asset(col, name, IMAGE_ASSET);
	if (asset)
		return (asset->asset);
	return (YNULL);
}

// Retrieve an text from asset list (or NULL if it doesn't exist)
t_string	*assets_get_text(t_asset_col *col, char *name)
{
	t_asset	*asset;

	asset = assets_get_asset(col, name, TEXT_ASSET);
	if (asset)
		return (asset->asset);
	return (YNULL);
}
