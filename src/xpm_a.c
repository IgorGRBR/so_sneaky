/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:40:26 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/19 15:40:32 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slxpm.h"
#include "slassets.h"
#include "slmlx.h"
#include "yio.h"
#include "ystring.h"
#include "ycstr.h"
#include <stdlib.h>
#include "yvec2.h"
#include "ylist.h"
#include <fcntl.h>

static t_bool	read_xpm_data(char *path, t_string *out)
{
	int			ifd;
	char		*line;
	char		*temp;
	t_string	*path_str;

	path_str = string_from_cstr(path);
	if (!try_open_file(path_str, O_RDONLY, &ifd))
		return (string_delete(path_str), FALSE);
	string_delete(path_str);
	line = get_next_line(ifd);
	while (line)
	{
		temp = cstr_trim(line, " \n");
		free(line);
		string_append_cstr(out, temp);
		free(temp);
		line = get_next_line(ifd);
	}
	return (TRUE);
}

static t_uint	read_header(char *xpm, t_uint i, t_ivec2 *sz, t_ivec2 *exdt)
{
	int	num;

	i = skip_until_char_in_set(xpm, "\"", i) + 1;
	if (i == 1)
		return (0);
	i = skip_whitespace(xpm, i);
	num = cstr_atoi(xpm + i);
	sz->x = num;
	i = skip_whitespace(xpm, skip_to_whitespace(xpm, i));
	num = cstr_atoi(xpm + i);
	sz->y = num;
	i = skip_whitespace(xpm, skip_to_whitespace(xpm, i));
	num = cstr_atoi(xpm + i);
	exdt->x = num;
	i = skip_whitespace(xpm, skip_to_whitespace(xpm, i));
	num = cstr_atoi(xpm + i);
	exdt->y = num;
	i = skip_until_char_in_set(xpm, "\"", i) + 1;
	if (i == 1)
		return (0);
	return (i);
}

static t_uint	read_palette(char *xpm, t_uint i, t_list *palette, t_ivec2 e)
{
	char	*key;
	int		j;

	j = 0;
	while (j < e.x)
	{
		i = skip_until_char_in_set(xpm, "\"", i) + 1;
		key = cstr_sub(xpm, i, e.y);
		i += e.y + 1;
		if (xpm[i] != 'c')
			error_exit("XPM palette format error");
		i += 2;
		if (xpm[i] != '#')
			error_exit("XPM palette format error");
		i++;
		if (cstr_ncmp(xpm + i, "None", 4) != 0)
			list_insert(palette,
				color_tuple_new(key, hex2color(cstr_sub(xpm, i, 6))));
		else
			list_insert(palette, color_tuple_new(key, argb_zero()));
		free(key);
		i = skip_until_char_in_set(xpm, "\"", i) + 2;
		j++;
	}
	return (i);
}

static t_bool	setup_image(t_image *img, char *xpm, t_uint i, t_ivec2 exdt)
{
	t_list	*palette;
	t_ivec2	brush;

	palette = list_new();
	i = read_palette(xpm, i, palette, exdt);
	brush = ivec2_zero();
	while (brush.y < img->size.y)
	{
		i = skip_until_char_in_set(xpm, "\"", i) + 1;
		brush.x = 0;
		while (brush.x < img->size.x)
		{
			image_set_pixel(img, brush.x, brush.y,
				get_color(palette, cstr_sub(xpm, i, exdt.y)));
			i += exdt.y;
			brush.x++;
		}
		i = skip_until_char_in_set(xpm, "\"", i) + 1;
		brush.y++;
	}
	list_apply(palette, (t_apply_func)color_tuple_delete);
	list_delete(palette);
	return (TRUE);
}

t_image	*load_image_from_xpm(char *path, t_mlx_context *mlx)
{
	t_string	*xpm_data;
	t_uint		i;
	t_ivec2		ex_data;
	t_image		*img;
	t_ivec2		size;

	xpm_data = string_new();
	ex_data = ivec2_zero();
	size = ivec2_zero();
	if (!read_xpm_data(path, xpm_data))
		error_exit("Can't open/read xpm file");
	i = skip_until_char_in_set(xpm_data->cstr, "{", 0);
	if (i == 0)
		error_exit("Could not find the start of xpm char* array");
	i = read_header(xpm_data->cstr, i, &size, &ex_data);
	if (i == 0)
		error_exit("Invalid xpm header");
	if (size.x == 0 || size.y == 0 || ex_data.x == 0
		|| ex_data.y == 0)
		error_exit("Invalid xpm header data");
	img = image_new(mlx, size);
	if (!setup_image(img, xpm_data->cstr, i, ex_data))
		error_exit("Image loading error");
	string_delete(xpm_data);
	return (img);
}
