/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slxpm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:40:12 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/19 15:40:18 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLXPM_H
# define SLXPM_H
# include "slcolor.h"
# include "ytypes.h"
# include "slassets.h"
# include "slmlx.h"

typedef struct s_xpm_tuple
{
	char	*key;
	t_argb	color;
}	t_xpm_tuple;

t_argb		hex2color(char *hex);
t_image		*load_image_from_xpm(char *path, t_mlx_context *mlx);
void		color_tuple_delete(t_xpm_tuple *tuple);
t_xpm_tuple	*color_tuple_new(char *key, t_argb color);
t_argb		get_color(t_list *palette, char *key);
t_uint		skip_whitespace(char *cstr, t_uint i);
t_uint		skip_to_whitespace(char *cstr, t_uint i);
t_uint		skip_until_char_in_set(char *cstr, char *set, t_uint i);

#endif
