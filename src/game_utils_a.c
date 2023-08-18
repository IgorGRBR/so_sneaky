/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:12:05 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/23 15:12:07 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slgame.h"
#include "yvec2.h"
#include "math.h"

void	calc_resolution_scaling(t_ivec2 window_size,
		int target_height,
		t_ivec2 *out_size, t_dvec2 *out_scale)
{
	double	scale_factor;
	double	aspect_ratio;

	scale_factor = (double)window_size.y / (double)target_height;
	out_scale->x = scale_factor;
	out_scale->y = scale_factor;
	aspect_ratio = (double)window_size.x / (double)window_size.y;
	out_size->y = target_height;
	out_size->x = (int)floor((double)target_height * aspect_ratio);
}
