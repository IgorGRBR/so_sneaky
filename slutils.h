/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slutils.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:09:00 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/10 14:09:17 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLUTILS_H
# define SLUTILS_H
# include "ytypes.h"

// Checks if 2 boxes intersect
t_bool	iaabb_test(t_ivec2 apos, t_ivec2 asize, t_ivec2 bpos, t_ivec2 bsize);

// Checks if 2 boxes intersect
t_bool	daabb_test(t_dvec2 apos, t_dvec2 asize, t_dvec2 bpos, t_dvec2 bsize);

#endif
