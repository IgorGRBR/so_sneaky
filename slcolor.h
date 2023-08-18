/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slcolor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:28:26 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/08 14:28:27 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLCOLOR_H
# define SLCOLOR_H
# include "ytypes.h"

typedef struct s_argb {
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}		t_argb;

t_argb	argb_new(t_uchar r, t_uchar g, t_uchar b, t_uchar a);
t_argb	argb_zero(void);

#endif
