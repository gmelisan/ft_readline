/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_search_history.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:37:14 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/30 05:48:34 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	reverse_search_history(t_line *line)
{
	line->hs.query = str_xcreate(0);
	line->hs_mode = 1;
	if (!line->hs.start)
	{
		line->hs.start = line->history->item;
		line->hs.original_cpos = line->cpos;
	}
}
