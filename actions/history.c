/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 00:53:19 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/18 04:39:42 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	previous_history(t_line *line)
{
	if (line->history->item->prev)
	{
		line->history->item = line->history->item->prev;
		line->str = (t_string *)line->history->item->content;
		line->cpos = line->str->len;
	}
}

void	next_history(t_line *line)
{
	if (line->history->item->next)
	{
		line->history->item = line->history->item->next;
		line->str = (t_string *)line->history->item->content;
		line->cpos = line->str->len;
	}
}
