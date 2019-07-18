/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:38:41 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/15 19:38:47 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	beginning_of_line(t_line *line)
{
	line->cpos = line->start;
}

void	end_of_line(t_line *line)
{
	line->cpos = line->str.len;
}

void	clear_screen(t_line *line)
{
	if (line)
		term_putstr("cl");
}
