/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:23:30 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/25 15:23:32 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slactor.h"
#include "slviewport.h"
#include "ylib.h"
#include <math.h>

static t_uint	get_frame(t_list *sprite, double dframe)
{
	t_uint	frame;

	frame = (t_uint)int_abs(floor(dframe)) % sprite->size;
	return (frame);
}

static t_image	*get_mirrored_image(t_actor *a, t_scene *scene, t_uint frame)
{
	t_image	*img;

	img = YNULL;
	if (a->direction == LEFT)
		img = list_get(
				scene->actor_sprites[a->type][a->state][RIGHT], frame);
	else if (a->direction == RIGHT)
		img = list_get(
				scene->actor_sprites[a->type][a->state][LEFT], frame);
	return (img);
}

void	actor_draw(t_actor *a, t_viewport *vp, t_scene *scene)
{
	t_image	*img;
	t_ivec2	dpos;
	double	xscale;
	t_uint	frame;

	dpos = ivec2_add(ivec2_new(a->position.x * TILE_WIDTH,
				a->position.y * TILE_HEIGHT), ivec2_new(16, 16));
	dpos = ivec2_add(dpos, a->draw_offset);
	xscale = 1.0;
	frame = 0;
	if (a->state == WALKING)
		frame = get_frame(
				scene->actor_sprites[a->type][a->state][a->direction],
				(1.0 - a->timer / ACTOR_MOVE_TIME) * 4.0);
	img = list_get(
			scene->actor_sprites[a->type][a->state][a->direction], frame);
	if (!img)
	{
		img = get_mirrored_image(a, scene, frame);
		xscale = -1.0;
	}
	if (img)
		viewport_draw_image(vp, img, dpos, dvec2_new(xscale, 1.0));
}
