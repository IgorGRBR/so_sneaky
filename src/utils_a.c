/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:11:13 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/10 14:11:26 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slutils.h"

t_bool	iaabb_test(t_ivec2 apos, t_ivec2 asize, t_ivec2 bpos, t_ivec2 bsize)
{
	if (apos.x <= bpos.x + bsize.x && apos.x + asize.x >= bpos.x
		&& apos.y <= bpos.y + bsize.y && apos.y + asize.y >= bpos.y)
		return (TRUE);
	return (FALSE);
}

t_bool	daabb_test(t_dvec2 apos, t_dvec2 asize, t_dvec2 bpos, t_dvec2 bsize)
{
	if (apos.x <= bpos.x + bsize.x && apos.x + asize.x >= bpos.x
		&& apos.y <= bpos.y + bsize.y && apos.y + asize.y >= bpos.y)
		return (TRUE);
	return (FALSE);
}
