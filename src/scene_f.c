/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:30:34 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/06/05 13:30:36 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slscene.h"
#include "slscene_types.h"
#include "ylib.h"

static void	confiugre_tile(t_scene *scene, t_ivec2 pos)
{
	t_node	node;

	node = scene->grid[pos.y][pos.x];
	if (pos.y > 0)
	{
		if ((node.tile == FLOOR || node.tile == EXIT_CLOSED)
			&& scene->grid[pos.y - 1][pos.x].tile == EMPTY)
		{
			scene->grid[pos.y - 1][pos.x].tile = TOP_WALL;
		}
	}
}

void	scene_setup_tiles_auto(t_scene *scene)
{
	t_ivec2	a;

	a = ivec2_zero();
	while (a.y < scene->size.y)
	{
		a.x = 0;
		while (a.x < scene->size.x)
		{
			confiugre_tile(scene, a);
			a.x++;
		}
		a.y++;
	}
}

t_bool	is_tile_solid(t_tile tile)
{
	return (tile != FLOOR && tile != EXIT && tile != EXIT_CLOSED
		&& tile != PURPLE_DOOR_OPEN && tile != PURPLE_DOOR_OPEN_H1
		&& tile != GREEN_DOOR_OPEN && tile != GREEN_DOOR_OPEN_H1
		&& tile != ORANGE_DOOR_OPEN && tile != ORANGE_DOOR_OPEN_H1);
}
