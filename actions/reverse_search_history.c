/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_search_history.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:37:14 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/27 00:24:24 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	reverse_search_history(t_line *line)
{
	line->search_string = str_xcreate(0);
	
	/* str_xaddback(line->str, "\n", 1); */
	/* str_xaddback(line->str, REV_I_SEARCH_STR, ft_strlen(REV_I_SEARCH_STR)); */
	/* str_xaddback(line->str, "\naaaaaaaaa", 10); */
	str_xaddback(line->str, "\na\nbb\nccc", 10);
}
