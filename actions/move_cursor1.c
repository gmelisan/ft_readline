/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:49:30 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/15 19:49:31 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	forward_char(t_line *line)
{
	if (line->cpos < (int)line->str.len)
		line->cpos++;
}

void	backward_char(t_line *line)
{
	if (line->cpos > line->start)
		line->cpos--;
}

void	forward_line(t_line *line)
{
	int w;

	w = get_screenwidth();
	if (line->cpos < w)
		return ;
	line->cpos -= w;
	if (line->cpos < line->start)
		line->cpos = line->start;
}

void	backward_line(t_line *line)
{
	int w;
	int last_col_start;

	w = get_screenwidth();
	last_col_start = (line->str.len / w) * w;
	if (line->cpos >= last_col_start)
		return ;
	line->cpos += w;
	if (line->cpos > (int)line->str.len)
		line->cpos = line->str.len;
}
