/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 07:10:23 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/28 21:26:12 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	self_insert(t_line *line)
{
	if (line->search_mode)
		str_xaddback(&line->search_string, line->keybuf, 1);
	else
	{
		if (line->overwrite_mode && line->cpos < (int)line->str->len)
			line->str->s[line->cpos] = *line->keybuf;
		else
			str_xinsert(line->str, line->cpos, line->keybuf, 1);
		line->cpos++;
	}
}
