/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:22:38 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/06/01 14:22:40 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slscene.h"
#include "slscene_types.h"

t_bool	is_pickup_item(t_item item)
{
	return (item == PURPLE_KEYCARD
		|| item == GREEN_KEYCARD
		|| item == ORANGE_KEYCARD);
}

void	scene_setup_player_state(t_scene *scene)
{
	scene->player_state.purple_keycard = FALSE;
	scene->player_state.green_keycard = FALSE;
	scene->player_state.orange_keycard = FALSE;
	scene->player_state.move_count = 0;
}

void	scene_on_item_pickup(t_scene *scene, t_item item)
{
	t_ivec2	epos;

	epos = scene->exit_pos;
	if (item == PURPLE_KEYCARD || item == GREEN_KEYCARD
		|| item == ORANGE_KEYCARD)
		scene->required_item_count--;
	if (scene->required_item_count == 0)
		scene->grid[epos.y][epos.x].tile = EXIT;
}

static const t_ivec2	g_dir[4] = {
{.x = 0, .y = -1},
{.x = 1, .y = 0},
{.x = 0, .y = 1},
{.x = -1, .y = 0},
};

void	scene_query_nearby(t_scene *scene, t_ivec2 pos, t_node *node[4])
{
	t_uint	i;
	t_ivec2	rpos;

	i = 0;
	while (i < 4)
	{
		rpos = ivec2_add(pos, g_dir[i]);
		if (rpos.x < 0 || rpos.x >= scene->size.x
			|| rpos.y < 0 || rpos.y >= scene->size.y)
			node[i] = YNULL;
		else
			node[i] = &scene->grid[rpos.y][rpos.x];
		i++;
	}
}
