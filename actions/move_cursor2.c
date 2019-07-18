/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:35:49 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/18 04:39:21 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

int		is_delim(char c)
{
	if (ft_isalnum(c))
		return (0);
	return (1);
}

void	forward_word(t_line *line)
{
	int i;

	i = line->cpos;
	while (is_delim(str_get(*line->str, i)) && i <= (int)line->str->len)
		i++;
	while (!is_delim(str_get(*line->str, i)) && i <= (int)line->str->len)
		i++;
	if (i > (int)line->str->len)
		i = line->str->len;
	line->cpos = i;
}

void	backward_word(t_line *line)
{
	int i;

	i = line->cpos;
	if (is_delim(str_get(*line->str, i - 1)))
		i--;
	while (is_delim(str_get(*line->str, i)) && i >= 0)
		i--;
	while (!is_delim(str_get(*line->str, i)) && i >= 0)
		i--;
	i++;
	line->cpos = i;
}
