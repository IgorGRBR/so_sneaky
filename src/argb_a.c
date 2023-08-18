/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:30:33 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/04 13:30:34 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slcolor.h"

t_argb	argb_new(t_uchar r, t_uchar g, t_uchar b, t_uchar a)
{
	return ((t_argb){.r = r, .g = g, .b = b, .a = a});
}

t_argb	argb_zero(void)
{
	return ((t_argb){.r = 0, .g = 0, .b = 0, .a = 0});
}
