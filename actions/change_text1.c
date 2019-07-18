/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_text1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:49:21 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/15 20:08:18 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	self_insert(t_line *line)
{
	if (line->overwrite_mode && line->cpos < (int)line->str.len)
		line->str.s[line->cpos] = *line->keybuf;
	else
		str_xinsert(&line->str, line->cpos, line->keybuf, 1);
	line->cpos++;
}

void	backward_delete_char(t_line *line)
{
	if (line->cpos > line->start)
	{
		line->cpos--;
		str_remove(&line->str, line->cpos, 1);
	}
}

void	delete_char(t_line *line)
{
	str_remove(&line->str, line->cpos, 1);
}

void	overwrite_mode(t_line *line)
{
	line->overwrite_mode ^= 1;
}
