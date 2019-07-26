/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escseqs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 23:45:47 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/26 18:08:55 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "escseqs.h"

/*
** Rule: "\E[n1;n2...]a", 
** n1, n2 - numbers
** [] - optional
** ... - can be repeated any times
** a - any char
** ------------
** ex.: "\E[m", "\E[0m", "\E[0;0m", "\E[4m", "\E[40;1m"
*/

static t_string	get_escseq(t_string str, int *i)
{
	t_string	es;
	int			j;
	int			len;

	j = *i + 1;
	es = str_copy("\033");
	if (str_get(str, j) != '[')
		return (es);
	str_xaddback(&es, str.s + j, 1);
	while (42)
	{
		len = 0;
		while (ft_isdigit(str_get(str, ++j)))
			len++;
		if (str_get(str, j) && len > 0)
			str_xaddback(&es, str.s + j - len, len);
		if (str_get(str, j) != ';')
			break ;
		else
			str_xaddback(&es, str.s + j, 1);
	}
	if (str_get(str, j))
		str_xaddback(&es, str.s + j, 1);
	*i = ++j;
	return (es);
}

void	pull_escseqs(t_vector *vec, t_string *str)
{
	t_string	new;
	t_string	tmp;
	char		c;
	int			i;

	*vec = vec_xcreate(0, sizeof(t_string));
	str_zero(&tmp);
	new = str_create(0);
	i = 0;
	while ((c = str_get(*str, i)))
	{
		if (c == ESC)
			tmp = get_escseq(*str, &i);
		else
		{
			vec_xaddback(vec, &tmp);
			str_xaddback(&new, &c, 1);
			str_zero(&tmp);
			i++;
		}
	}
	free(str->s);
	*str = new;
}
