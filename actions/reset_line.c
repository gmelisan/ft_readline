/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 16:37:41 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/30 16:46:27 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	reset_line(t_line *line)
{
	while (line->history->item->next)
		line->history->item = line->history->item->next;
	line->str = (t_string *)line->history->item->content;
	str_delete(line->str);
	*line->str = str_xcreate(0);
	line->cpos = 0;
	line->hs_mode = 0;
	ft_putstr("\n");
}
