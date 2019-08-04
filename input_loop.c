/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:40:53 by gmelisan          #+#    #+#             */
/*   Updated: 2019/08/03 03:44:15 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_loop.h"

static void		perform_action(t_line *line, t_vector *key_bindings)
{
	t_binding	*b;

	b = find_binding(key_bindings, line->keybuf);
	if (b && b->action)
	{
		(*b->action)(line);
		if (b->action != &self_insert
			&& b->action != &backward_delete_char
			&& b->action != &reverse_search_history)
			line->hs_mode = 0;
		if (line->hs_mode)
			hs_prepare_line(line);
		else
			str_delete(&line->hs.query);
		update_line(line);
		if (line->hs_mode)
			hs_clear(line);
	}
}

static int		is_ansiseq(char buf[KEYBUF_SIZE])
{
	if (buf[0] == ESC && (buf[1] == '[' || buf[1] == 'O'))
		return (1);
	return (0);
}

int				input_loop(t_line *line, t_vector *key_bindings)
{
	int		ret;

	if (line->vi_mode)
		return (vi_input_loop(line, key_bindings));
	while ((ret = read(STDIN, line->keybuf, 1) > 0 && *line->keybuf != NL))
	{
		if (*line->keybuf == ESC)
		{
			if ((ret = read(STDIN, line->keybuf + 1, 1)) <= 0)
				break ;
			if (is_ansiseq(line->keybuf))
				if ((ret = read(STDIN, line->keybuf + 2, KEYBUF_SIZE - 3)) <= 0)
					break ;
		}
		if (*line->keybuf == CTRL_D && line->str->len == 0)
			return (1);
		perform_action(line, key_bindings);
		loginfo_line(line);
		ft_bzero(line->keybuf, KEYBUF_SIZE);
	}
	if (ret < 0)
		g_errno = ERROR_READ;
	return (0);
}

int				vi_input_loop(t_line *line, t_vector *key_bindings)
{
	int		ret;

	while ((ret = read(STDIN, line->keybuf, KEYBUF_SIZE - 1)) &&
			*line->keybuf != NL)
	{
		if (line->keybuf[0] == ESC && line->keybuf[1] == 0)
			line->vi_mode = VI_COMMAND;
		
	}
}
