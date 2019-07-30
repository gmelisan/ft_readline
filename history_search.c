/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:51:21 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/30 06:10:11 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_search.h"

void	hs_find(t_line *line)
{
	t_dlist	*i;
	char	*res;

	if (line->hs.query.len == 0)
	{
		line->history->item = line->hs.start;
		line->str = (t_string *)line->history->item->content;
		line->cpos = line->hs.original_cpos;
		return ;
	}
	i = line->hs.start;
	while (i)
	{
		res = ft_strrstr(((t_string *)i->content)->s, line->hs.query.s);
		if (res)
		{
			line->hs.fail = 0;
			line->hs.pos = res;
			line->str = (t_string *)i->content;
			line->history->item = i;
			return ;
		}
		i = i->prev;
	}
	line->hs.fail = 1;
}

static void	hs_decorate(t_line *line)
{
	int	i;
	int	j;

	i = -1;
	while (str_get(*line->str, ++i))
	{
		if (line->hs.pos == &line->str->s[i])
		{
			line->cpos = i;
			j = 0;
			str_xinsert(line->str, i, UNDERLINE_SEQ, ft_strlen(UNDERLINE_SEQ));
			i += ft_strlen(UNDERLINE_SEQ);
			while (str_get(line->hs.query, ++j) ==
				   str_get(*line->str, ++i) && str_get(*line->str, i));
			str_xinsert(line->str, i, RESET_SEQ, ft_strlen(RESET_SEQ));
			break ;
		}
	}
}

void	hs_prepare_line(t_line *line)
{
	t_string	out_hs_string;

	line->hs.original_str = str_xduplicate(*line->str);
	hs_decorate(line);
	str_xaddback(line->str, "\n", 1);
	out_hs_string = str_xcopy(REVISRCH_STR);
	if (line->hs.fail)
		str_xaddfront(&out_hs_string, FAILSRCH_STR, ft_strlen(FAILSRCH_STR));
	str_xaddback(&out_hs_string, line->hs.query.s, line->hs.query.len);
	str_xaddback(&out_hs_string, "_", 1);
	str_xaddback(line->str, out_hs_string.s, ft_strlen(out_hs_string.s));
	str_delete(&out_hs_string);
}

void	hs_clear(t_line *line)
{
	/* int	nl; */

	/* nl = -1; */
	/* while (str_get(*line->str, ++nl)) */
	/* 	if (str_get(*line->str, nl) == '\n') */
	/* 		break; */
	/* if (str_get(*line->str, nl)) */
	/* { */
	/* 	ft_bzero(line->str->s + nl, line->str->len - nl); */
	/* 	line->str->len = nl; */
	/* } */
	str_delete(line->str);
	*line->str = line->hs.original_str;
}
