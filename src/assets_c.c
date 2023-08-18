/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:53:18 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/23 13:53:19 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slassets.h"
#include "slmlx.h"
#include "ycstr.h"
#include "ylib.h"
#include "ytypes.h"
#include <fcntl.h>
#include <stdlib.h>

static t_bool	load_image_routine(t_asset_col *col, t_mlxc *mlxc,
	t_string *token[5])
{
	t_bool	success;
	t_image	*img;

	success = assets_load_image_tga(col, mlxc, token[1]->cstr, token[2]->cstr);
	if (success && token[3] && token[4])
	{
		img = assets_get_image(col, token[1]->cstr);
		img->origin.x = cstr_atoi(token[3]->cstr);
		img->origin.y = cstr_atoi(token[4]->cstr);
	}
	return (success);
}

static void	parse_tokens(t_list *tokens, t_asset_col *col, t_mlxc *mlxc)
{
	t_string	*token[5];
	t_bool		success;
	char		*err_msg;
	int			i;

	i = -1;
	while (++i < 5)
		token[i] = list_get(tokens, i);
	if (token[0]->cstr[0] == '#')
		return ;
	success = FALSE;
	if (cstr_ncmp(token[0]->cstr, "i", token[0]->size) == 0)
		success = load_image_routine(col, mlxc, token);
	else if (cstr_ncmp(token[0]->cstr, "t", token[0]->size) == 0)
		success = assets_load_text(col, token[1]->cstr, token[2]->cstr);
	else
		error_exit("Asset list file parsing error");
	err_msg = "Could not load an asset ";
	if (!success)
		error_exit(cstr_join(err_msg, token[1]->cstr));
}

static void	parse_asset_collection(t_list *lines, t_asset_col *col,
			t_mlxc *mlxc)
{
	t_list_iter	it;
	t_string	*line_nl;
	t_string	*line;
	t_list		*tokens;

	it = list_iter(lines);
	while (list_iter_next(&it))
	{
		line_nl = string_from_cstr(it.value);
		line = string_trim_cstr(line_nl, "\n");
		tokens = string_split(line, ' ');
		if (tokens && tokens->size > 0)
			parse_tokens(tokens, col, mlxc);
		if (tokens)
		{
			list_apply(tokens, (t_apply_func)string_delete);
			list_delete(tokens);
		}
		string_delete(line);
		string_delete(line_nl);
	}
}

void	assets_load_from_file(t_asset_col *col, t_mlxc *mlxc, char *path)
{
	int			ifd;
	t_string	*path_str;
	char		*line;
	t_list		*lines;

	if (!col)
		return ;
	path_str = string_from_cstr(path);
	if (!try_open_file(path_str, O_RDONLY, &ifd))
		error_exit("Invalid asset collection file path");
	string_delete(path_str);
	line = get_next_line(ifd);
	lines = list_new();
	while (line)
	{
		list_insert(lines, line);
		line = get_next_line(ifd);
	}
	parse_asset_collection(lines, col, mlxc);
	list_apply(lines, free);
	list_delete(lines);
}
