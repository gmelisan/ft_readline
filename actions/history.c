/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 00:53:19 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/18 02:58:11 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	previous_history(t_line *line)
{
	char *s;

	//history_push(line->history, line->str.s + line->start);
	if (line->history->item->prev)
	{
		line->history->item = line->history->item->prev;
		ft_bzero(line->str.s + line->start, line->str.len - line->start);
		line->str.len = line->start;
		s = (char *)line->history->item->content;
		str_xaddback(&line->str, s, ft_strlen(s));
		line->cpos = line->str.len;
	}
}

void	next_history(t_line *line)
{
	char *s;

	//history_push(line->history, line->str.s + line->start);
	if (line->history->item->next)
	{
		line->history->item = line->history->item->next;
		ft_bzero(line->str.s + line->start, line->str.len - line->start);
		line->str.len = line->start;
		s = (char *)line->history->item->content;
		str_xaddback(&line->str, s, ft_strlen(s));
		line->cpos = line->str.len;
	}
}
