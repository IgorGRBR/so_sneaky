/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:02:11 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/25 15:02:12 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slassets.h"
#include "slscene.h"
#include "slscene_types.h"
#include "slactor.h"
#include "slviewport.h"
#include "ylib.h"

static void	viewport_control(t_actor *target, t_viewport *vp, double dt)
{
	t_ivec2		vp_halfsize;
	t_ivec2		target_pos;
	t_ivec2		diff;

	(void)dt;
	vp_halfsize = ivec2_divide(vp->surface->size, 2);
	target_pos = ivec2_sub(ivec2_scale(target->position, 32), vp_halfsize);
	target_pos = ivec2_add(ivec2_add(target_pos, ivec2_new(16, 16)),
			target->draw_offset);
	diff = ivec2_divide(ivec2_sub(target_pos, vp->t_pos), 8);
	vp->t_pos = ivec2_add(vp->t_pos, diff);
}

t_update_status	scene_update(t_scene *scene, double dt, t_game_data *game)
{
	t_list_iter	it;

	it = list_iter(scene->actors);
	while (list_iter_next(&it))
		actor_update(it.value, game, dt);
	if (scene->player)
		player_update(scene->player, game, scene, dt);
	it = list_iter(scene->patrols);
	while (list_iter_next(&it))
		patrol_update(it.value, game, scene, dt);
	if (scene->camera_focus_actor)
		viewport_control(scene->camera_focus_actor,
			list_get(game->gfx->views, 0), dt);
	return (scene->update_status);
}

static const t_ivec2	g_grid_size = {.x = TILE_WIDTH, .y = TILE_HEIGHT};

static void	draw_node(t_scene *scene, t_ivec2 pos, t_viewport *vp)
{
	t_image	*image;
	t_node	node;
	t_ivec2	dpos;

	node = scene->grid[pos.y][pos.x];
	image = scene->tileset[node.tile];
	if (image)
	{
		dpos.x = pos.x * g_grid_size.x;
		dpos.y = pos.y * g_grid_size.y;
		viewport_draw_image(vp, image, dpos, dvec2_new(1.0, 1.0));
	}
	image = scene->item_images[node.item];
	if (image)
	{
		dpos.x = pos.x * g_grid_size.x + TILE_WIDTH / 2;
		dpos.y = pos.y * g_grid_size.y + TILE_HEIGHT / 2;
		viewport_draw_image(vp, image, dpos, dvec2_new(1.0, 1.0));
	}
}

static void	draw_front_tile(t_scene *scene, t_ivec2 pos, t_viewport *vp)
{
	t_image	*image;
	t_ivec2	dpos;

	image = scene->tileset[scene->grid[pos.y][pos.x].front_tile];
	if (image)
	{
		dpos.x = pos.x * g_grid_size.x;
		dpos.y = pos.y * g_grid_size.y;
		viewport_draw_image(vp, image, dpos, dvec2_new(1.0, 1.0));
	}
}

void	scene_draw(t_scene *scene, t_viewport *vp)
{
	t_ivec2		brush;
	t_list_iter	it;

	brush.y = -1;
	while (++brush.y < scene->size.y)
	{
		brush.x = -1;
		while (++brush.x < scene->size.x)
			draw_node(scene, brush, vp);
	}
	it = list_iter(scene->actors);
	while (list_iter_next(&it))
		actor_draw(it.value, vp, scene);
	brush.y = -1;
	while (++brush.y < scene->size.y)
	{
		brush.x = -1;
		while (++brush.x < scene->size.x)
			draw_front_tile(scene, brush, vp);
	}
}
