/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:41:17 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/08 14:41:39 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slgame.h"
#include "slmlx.h"
#include "yprint.h"
#include "ystring.h"
#include "ycstr.h"
#include "ylist.h"
#include "yio.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "yvec2.h"

static t_game_config	zero_game_config(void)
{
	return ((t_game_config){
		.window_size = ivec2_new(1280, 720),
		.up_keycode = 0,
		.down_keycode = 0,
		.left_keycode = 0,
		.right_keycode = 0,
		.action_keycode = 0,
		.cancel_keycode = 0,
		.quit_keycode = 0,
		.debug_keycode = 0,
	});
}

static void	parse_param2(t_game_config *c, char *p, char *p2, char *p3);

static void	parse_param(t_game_config *c, char *p, char *p2, char *p3)
{
	t_uint	p_len;

	p_len = cstr_len(p);
	if (cstr_ncmp(p, "window_size", p_len) == 0)
		c->window_size = ivec2_new(cstr_atoi(p2), cstr_atoi(p3));
	else if (cstr_ncmp(p, "up_code", p_len) == 0)
		c->up_keycode = (t_uint)cstr_atoi(p2);
	else if (cstr_ncmp(p, "down_code", p_len) == 0)
		c->down_keycode = (t_uint)cstr_atoi(p2);
	else if (cstr_ncmp(p, "left_code", p_len) == 0)
		c->left_keycode = (t_uint)cstr_atoi(p2);
	else if (cstr_ncmp(p, "right_code", p_len) == 0)
		c->right_keycode = (t_uint)cstr_atoi(p2);
	else if (cstr_ncmp(p, "action_code", p_len) == 0)
		c->action_keycode = (t_uint)cstr_atoi(p2);
	else if (cstr_ncmp(p, "cancel_code", p_len) == 0)
		c->cancel_keycode = (t_uint)cstr_atoi(p2);
	else if (cstr_ncmp(p, "quit_code", p_len) == 0)
		c->quit_keycode = (t_uint)cstr_atoi(p2);
	else if (cstr_ncmp(p, "debug_code", p_len) == 0)
		c->debug_keycode = (t_uint)cstr_atoi(p2);
	else
		parse_param2(c, p, p2, p3);
}

static void	parse_param2(t_game_config *c, char *p, char *p2, char *p3)
{
	t_uint	p_len;

	p_len = cstr_len(p);
	if (cstr_ncmp(p, "window_size", p_len) == 0)
		c->window_size = ivec2_new(cstr_atoi(p2), cstr_atoi(p3));
	else
		error_exit("Unknown config parameter");
}

t_game_config	load_game_config(const char *filepath, char *line_cstr)
{
	int				ifd;
	t_list			*line_list;
	t_string		*line_str;
	t_string		*line_temp;
	t_game_config	cfg;

	cfg = zero_game_config();
	if (!try_open_file_cstr(filepath, O_RDONLY, &ifd))
		error_exit("Couldn't open config file");
	line_cstr = get_next_line(ifd);
	while (line_cstr)
	{
		line_str = string_from_cstr(line_cstr);
		(free(line_cstr), line_temp = string_trim_cstr(line_str, " \n"));
		(string_delete(line_str), line_list = string_split(line_temp, ' '));
		list_insert(line_list, string_new());
		if (line_list->size > 2 && line_temp->cstr[0] != '#')
			parse_param(&cfg, ((t_string *)list_get(line_list, 0))->cstr,
				((t_string *)list_get(line_list, 1))->cstr,
				((t_string *)list_get(line_list, 2))->cstr);
		(list_apply(line_list, (t_apply_func)string_delete));
		(string_delete(line_temp), list_delete(line_list));
		line_cstr = get_next_line(ifd);
	}
	return (cfg);
}

void	print_config(t_game_config c)
{
	yprintf("Game config:\n\tUp code: %d\n\tDown code: %d",
		c.up_keycode, c.down_keycode);
	yprintf("\n\tLeft code: %d\n\tRight code: %d\n\tAction code: %d\n\t",
		c.left_keycode, c.right_keycode, c.action_keycode);
	yprintf("Cancel code: %d\n\tQuit code: %d\n\tDebug code: %d\n\t",
		c.cancel_keycode, c.quit_keycode, c.debug_keycode);
	yprintf("Window size: (%d, %d)\n",
		c.window_size.x, c.window_size.y);
}
