/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:28:41 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/06/12 14:28:43 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slscene.h"
#include "slassets.h"

static void	setup_more_tiles(t_scene *scene, t_asset_col *assets)
{
	scene->tileset[PURPLE_DOOR_OPEN_H1] = assets_get_image(assets,
			"purple_door_ho1");
	scene->tileset[PURPLE_DOOR_OPEN_H2] = assets_get_image(assets,
			"purple_door_ho2");
	scene->tileset[PURPLE_DOOR_CLOSED_H1] = assets_get_image(assets,
			"purple_door_hc1");
	scene->tileset[PURPLE_DOOR_CLOSED_H2] = assets_get_image(assets,
			"purple_door_hc2");
	scene->tileset[GREEN_DOOR_OPEN_H1] = assets_get_image(assets,
			"green_door_ho1");
	scene->tileset[GREEN_DOOR_OPEN_H2] = assets_get_image(assets,
			"green_door_ho2");
	scene->tileset[GREEN_DOOR_CLOSED_H1] = assets_get_image(assets,
			"green_door_hc1");
	scene->tileset[GREEN_DOOR_CLOSED_H2] = assets_get_image(assets,
			"green_door_hc2");
	scene->tileset[ORANGE_DOOR_OPEN_H1] = assets_get_image(assets,
			"orange_door_ho1");
	scene->tileset[ORANGE_DOOR_OPEN_H2] = assets_get_image(assets,
			"orange_door_ho2");
	scene->tileset[ORANGE_DOOR_CLOSED_H1] = assets_get_image(assets,
			"orange_door_hc1");
	scene->tileset[ORANGE_DOOR_CLOSED_H2] = assets_get_image(assets,
			"orange_door_hc2");
}

void	_setup_scene_tileset(t_scene *scene, t_asset_col *assets)
{
	scene->tileset[EMPTY] = assets_get_image(assets, "tile_empty");
	scene->tileset[FLOOR] = assets_get_image(assets, "tile_floor");
	scene->tileset[TOP_WALL] = assets_get_image(assets, "tile_wall");
	scene->tileset[EXIT] = assets_get_image(assets, "tile_open_exit");
	scene->tileset[EXIT_CLOSED] = assets_get_image(assets,
			"tile_closed_exit");
	scene->tileset[PURPLE_DOOR_OPEN] = assets_get_image(assets,
			"purple_door_vo");
	scene->tileset[PURPLE_DOOR_CLOSED] = assets_get_image(assets,
			"purple_door_vc");
	scene->tileset[GREEN_DOOR_OPEN] = assets_get_image(assets,
			"green_door_vo");
	scene->tileset[GREEN_DOOR_CLOSED] = assets_get_image(assets,
			"green_door_vc");
	scene->tileset[ORANGE_DOOR_OPEN] = assets_get_image(assets,
			"orange_door_vo");
	scene->tileset[ORANGE_DOOR_CLOSED] = assets_get_image(assets,
			"orange_door_vc");
	setup_more_tiles(scene, assets);
}
