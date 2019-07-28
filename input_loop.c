/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:40:53 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/28 20:23:17 by gmelisan         ###   ########.fr       */
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
			line->search_mode = 0;
		if (line->search_mode)
			hs_prepare_line(line);
		else
			str_delete(&line->search_string);
		update_line(line);
		hs_clear(line);
	}
}

static int		is_ansiseq(char buf[KEYBUF_SIZE])
{
	if (buf[0] == ESC && (buf[1] == '[' || buf[1] == 'O'))
		return (1);
	return (0);
}

static void		loginfo(t_line *line)
{
	char c;

	c = line->keybuf[0];
	ft_fdprintf(g_logfd, "-> (%c) [%d %d %d %d %d %d], str: \"%s\", pos: %d\n",
				ft_isprint(c) ? c : ' ',
				line->keybuf[0], line->keybuf[1],
				line->keybuf[2], line->keybuf[3],
				line->keybuf[4], line->keybuf[5],
				line->str->s, line->cpos);
}

int				input_loop(t_line *line, t_vector *key_bindings)
{
	int		ret;

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
		loginfo(line);
		ft_bzero(line->keybuf, KEYBUF_SIZE);
	}
	if (ret < 0)
		g_errno = ERROR_READ;
	return (0);
}
