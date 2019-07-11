/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 22:05:18 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/11 03:26:51 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	self_insert(t_line *line)
{
	str_xinsert(&line->str, line->cpos, line->keybuf, 1);
	line->cpos++;
}

void	backspace(t_line *line)
{
	if (line->cpos > line->start)
	{
		line->cpos--;
		str_remove(&line->str, line->cpos, 1);
	}
}

void	delete(t_line *line)
{
	str_remove(&line->str, line->cpos, 1);
}

void	move_forward(t_line *line)
{
	if (line->cpos < (int)line->str.len)
		line->cpos++;
}

void	move_backward(t_line *line)
{
	if (line->cpos > line->start)
		line->cpos--;
}

void	clear_screen(t_line *line)
{
	if (line)
		term_putstr("cl");
}

void	goto_start(t_line *line)
{
	line->cpos = line->start;
}

void	goto_end(t_line *line)
{
	line->cpos = line->str.len;
}

static void	swap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_chars(t_line *line)
{
	int		pos;

	if (line->cpos == line->start ||
		line->str.len - line->start <= 1)
		return ;
	pos = line->cpos;
	if (line->cpos == (int)line->str.len)
		swap(&line->str.s[pos - 2], &line->str.s[pos - 1]);
	else
		swap(&line->str.s[pos - 1], &line->str.s[pos]);
	move_forward(line);
}
