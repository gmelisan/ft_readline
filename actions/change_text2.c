/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_text2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:43:09 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/15 20:59:08 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

static void	swap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	transpose_chars(t_line *line)
{
	int		pos;

	if (line->cpos == line->start ||
		line->str.len - line->start <= 1)
		return ;
	pos = line->cpos;
	if (line->cpos == (int)line->str.len)
		swap(&line->str.s[pos - 2], &line->str.s[pos - 1]);
	else
		swap(&line->str.s[pos - 1], &line->str.s[pos]);
	forward_char(line);
}

/* TODO: meta/alt bindings */
void	transpose_words(t_line *line)
{
	if (line)
		return ;
}
