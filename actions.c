/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 22:05:18 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/08 17:41:04 by gmelisan         ###   ########.fr       */
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
