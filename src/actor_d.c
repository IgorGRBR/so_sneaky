/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:28:25 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/06/12 14:28:29 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slactor.h"
#include "slscene.h"
#include "ylib.h"
#include "ymath.h"

#define SQRT_OF_4 (0.7071067811865475)
#define MAX_VISION_DIST (4)

static const t_dvec2	g_dir_vec[4] = {
{.x = 0.0, .y = -1.0},
{.x = 1.0, .y = 0.0},
{.x = 0.0, .y = 1.0},
{.x = -1.0, .y = 0.0},
};

static t_uint	check_node(t_scene *scene, t_actor *a, t_ivec2 pos)
{
	if (pos.x >= 0 && pos.x < scene->size.x
		&& pos.y >= 0 && pos.y < scene->size.y)
	{
		if (scene->grid[pos.y][pos.x].actor == a)
			return (2);
		if (is_tile_solid(scene->grid[pos.y][pos.x].tile))
			return (1);
	}
	return (0);
}

// q_status contains the status of node query:
// 0 means nothing
// 1 means a solid wall was found
// 2 means the searched actor was found
static t_bool	vstep_through(t_scene *scene, t_actor *a, t_actor *b,
				t_dvec2 step)
{
	t_ivec2	pos;
	t_ivec2	st_dir;
	t_uint	dist;
	t_dvec2	acm;
	t_uint	q_status;

	acm = dvec2_new(0.5, 0.5);
	st_dir = ivec2_new(double_sign(step.x), double_sign(step.y));
	step = dvec2_new(step.x * (double)st_dir.x, step.y * (double)st_dir.y);
	dist = 0;
	pos = a->position;
	q_status = 0;
	while (dist * dist < MAX_VISION_DIST * MAX_VISION_DIST)
	{
		acm = dvec2_add(acm, step);
		(void)!((acm.x >= 1.0) && (pos.x += st_dir.x, acm.x -= 1.0,
			q_status = check_node(scene, b, pos), dist++));
		if (q_status > 0)
			return (q_status == 2);
		(void)!((acm.y >= 1.0) && (pos.y += st_dir.y, acm.y -= 1.0,
			q_status = check_node(scene, b, pos), dist++));
		if (q_status > 0)
			return (q_status == 2);
	}
	return (FALSE);
}

// The exact same procedure as v_step_through, but the order of horizontal
// and vertical steps is swapped
static t_bool	hstep_through(t_scene *scene, t_actor *a, t_actor *b,
				t_dvec2 step)
{
	t_ivec2	pos;
	t_ivec2	st_dir;
	t_uint	dist;
	t_dvec2	acm;
	t_uint	q_status;

	acm = dvec2_new(0.5, 0.5);
	st_dir = ivec2_new(double_sign(step.x), double_sign(step.y));
	step = dvec2_new(step.x * (double)st_dir.x, step.y * (double)st_dir.y);
	dist = 0;
	pos = a->position;
	q_status = 0;
	while (dist * dist < MAX_VISION_DIST * MAX_VISION_DIST)
	{
		acm = dvec2_add(acm, step);
		(void)!((acm.y >= 1.0) && (pos.y += st_dir.y, acm.y -= 1.0,
			q_status = check_node(scene, b, pos), dist++));
		if (q_status > 0)
			return (q_status == 2);
		(void)!((acm.x >= 1.0) && (pos.x += st_dir.x, acm.x -= 1.0,
			q_status = check_node(scene, b, pos), dist++));
		if (q_status > 0)
			return (q_status == 2);
	}
	return (FALSE);
}

t_bool	actor_vision_test(t_scene *scene, t_actor *a, t_actor *b)
{
	t_dvec2	ab_diff;

	ab_diff = ivec2_normalized(ivec2_sub(b->position, a->position));
	if (dvec2_dot(g_dir_vec[a->direction], ab_diff) >= SQRT_OF_4)
	{
		if (a->direction == LEFT || a->direction == RIGHT)
			return (hstep_through(scene, a, b, ab_diff));
		else
			return (vstep_through(scene, a, b, ab_diff));
	}
	return (FALSE);
}
