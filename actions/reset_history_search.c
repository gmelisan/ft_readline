/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_history_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 03:29:20 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/30 06:16:33 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	reset_history_search(t_line *line)
{
	if (line->hs_mode)
	{
		line->history->item = line->hs.start;
		line->str = (t_string *)line->history->item->content;
		/* line->cpos = line->str->len; */
		line->cpos = line->hs.original_cpos;
		line->hs_mode = 0;
	}
	else
	{
		str_delete(line->str);
		*line->str = str_xcreate(0);
		line->cpos = 0;
		ft_putstr("\n");
	}
}
