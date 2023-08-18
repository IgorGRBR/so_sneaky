/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:40:35 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/19 15:40:39 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slxpm.h"
#include "ytypes.h"
#include "slcolor.h"
#include "ychar.h"
#include "ylist.h"
#include <stdlib.h>
#include "ycstr.h"

t_xpm_tuple	*color_tuple_new(char *key, t_argb color)
{
	t_xpm_tuple	*tuple;

	tuple = (t_xpm_tuple *)malloc(sizeof(t_xpm_tuple));
	tuple->key = cstr_dup(key);
	tuple->color = color;
	return (tuple);
}

void	color_tuple_delete(t_xpm_tuple *tuple)
{
	free(tuple->key);
	free(tuple);
}

static t_uint	h2i(char h)
{
	static const char	*c = "0123456789ABCDEF";
	t_uint				i;

	i = 0;
	while (i < 16)
	{
		if (h == c[i])
			return (i);
		i++;
	}
	return (16);
}

t_argb	hex2color(char *hex)
{
	t_uint	i;
	t_argb	c;

	i = 0;
	while (hex[i])
	{
		hex[i] = to_upper(hex[i]);
		if ((hex[i] > 'F' || hex[i] < 'A') && (hex[i] > '9' || hex[i] < '0'))
			error_exit("XPM invalid hex color format");
		i++;
	}
	c.a = 255;
	c.r = h2i(hex[0]) * 16 + h2i(hex[1]);
	c.g = h2i(hex[2]) * 16 + h2i(hex[3]);
	c.b = h2i(hex[4]) * 16 + h2i(hex[5]);
	free(hex);
	return (c);
}

t_argb	get_color(t_list *palette, char *key)
{
	t_list_iter	it;
	t_uint		len;

	it = list_iter(palette);
	len = cstr_len(key);
	while (list_iter_next(&it))
	{
		if (cstr_ncmp(key, ((t_xpm_tuple *)it.value)->key, len) == 0)
			return (free(key), ((t_xpm_tuple *)it.value)->color);
	}
	error_exit("XPM invalid color key");
	return (argb_zero());
}
