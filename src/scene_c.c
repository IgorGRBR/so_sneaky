/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:21:30 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/24 14:21:31 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slscene.h"
#include "slgame.h"
#include "slassets.h"
#include "slscene_types.h"
#include "yprint.h"
#include "ylib.h"
#include "slviewport.h"
#include <stdlib.h>

static const char	*g_actor_type_names[ACTOR_TYPE_COUNT] = {
	"mc_", "enemy_", "rat_"
};

static const char	*g_actor_state_names[ACTOR_STATE_COUNT] = {
	"idle_", "walk_", "action_", "neutralized_", "hidden_"
};

static const t_uint	g_actor_state_count[ACTOR_STATE_COUNT] = {
	1, 4, 4, 1, 1
};

static const char	*g_actor_direction_names[4] = {
	"u_", "r_", "d_", "l_"
};

static t_image	*get_image(t_uint i[4], t_asset_col *col)
{
	char	*str[3];
	t_image	*img;

	str[0] = cstr_join(g_actor_type_names[i[0]],
			g_actor_state_names[i[1]]);
	str[1] = cstr_join(str[0], g_actor_direction_names[i[2]]);
	free(str[0]);
	str[2] = cstr_itoa(i[3]);
	str[0] = cstr_join(str[1], str[2]);
	(free(str[1]), free(str[2]));
	img = assets_get_image(col, str[0]);
	free(str[0]);
	if (img)
	{
		img->origin.x = img->size.x / 2;
		img->origin.y = img->size.y;
	}
	return (img);
}

static void	setup_assets2(t_scene *scene, t_asset_col *assets)
{
	t_uint	i[4];

	i[0] = 0;
	while (i[0] < ACTOR_TYPE_COUNT)
	{
		i[1] = 0;
		while (i[1] < ACTOR_STATE_COUNT)
		{
			i[2] = 0;
			while (i[2] < 4)
			{
				scene->actor_sprites[i[0]][i[1]][i[2]] = list_new();
				i[3] = 0;
				while (i[3] < g_actor_state_count[i[1]])
				{
					list_insert(scene->actor_sprites[i[0]][i[1]][i[2]],
						get_image(i, assets));
					i[3]++;
				}
				i[2]++;
			}
			i[1]++;
		}
		i[0]++;
	}
}

static void	setup_assets1(t_scene *scene, t_asset_col *assets)
{
	t_uint	i;

	scene->item_images[NO_ITEM] = YNULL;
	scene->item_images[PURPLE_KEYCARD] = assets_get_image(assets, "purple_kc");
	scene->item_images[GREEN_KEYCARD] = assets_get_image(assets, "green_kc");
	scene->item_images[ORANGE_KEYCARD] = assets_get_image(assets, "orange_kc");
	i = 0;
	while (i < ITEM_TYPE_COUNT)
	{
		if (scene->item_images[i])
			scene->item_images[i]->origin = ivec2_divide(
					scene->item_images[i]->size, 2);
		i++;
	}
	setup_assets2(scene, assets);
}

void	setup_scene_assets(t_scene *scene, t_asset_col *assets, t_mlxc *mlxc)
{
	if (scene->asset_path)
	{
		yprintf("Loading scene assets...");
		assets_load_from_file(assets, mlxc, scene->asset_path->cstr);
	}
	_setup_scene_tileset(scene, assets);
	setup_assets1(scene, assets);
}
