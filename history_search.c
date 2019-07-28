/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:51:21 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/28 20:06:49 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_search.h"

void	hs_prepare_line(t_line *line)
{
	t_string	out_search_string;

	str_xaddback(line->str, "\n", 1);
	out_search_string = str_xcopy(REV_I_SEARCH_STR);
	str_xaddback(&out_search_string, line->search_string.s,
													line->search_string.len);
	str_xaddback(&out_search_string, "_", 1);
	str_xaddback(line->str, out_search_string.s,
											ft_strlen(out_search_string.s));
}

void	hs_clear(t_line *line)
{
	int	nl;

	nl = -1;
	while (str_get(*line->str, ++nl))
		if (str_get(*line->str, nl) == '\n')
			break;
	if (str_get(*line->str, nl))
	{
		ft_bzero(line->str->s + nl, line->str->len - nl);
		line->str->len = nl;
	}
}
