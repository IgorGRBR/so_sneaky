/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:45:05 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/19 15:45:06 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slxpm.h"

t_uint	skip_whitespace(char *cstr, t_uint i)
{
	char	c;

	c = cstr[i];
	while (c == ' ' || c == '\n' || c == '\t')
	{
		i++;
		c = cstr[i];
		if (c == '\0')
			return (0);
	}
	return (i);
}

t_uint	skip_to_whitespace(char *cstr, t_uint i)
{
	char	c;

	c = cstr[i];
	while (c != ' ' && c != '\n' && c != '\t')
	{
		i++;
		c = cstr[i];
		if (c == '\0')
			return (0);
	}
	return (i);
}

t_uint	skip_until_char_in_set(char *cstr, char *set, t_uint i)
{
	t_uint	j;

	while (cstr[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == cstr[i])
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}
