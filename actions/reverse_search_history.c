/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_search_history.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:37:14 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/27 21:18:48 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	reverse_search_history(t_line *line)
{
	char a[] = "\n\E[0;31ma\E[maa";
	char b[] = "\nb\E[0;32mb\E[0mb";
	char c[] = "\ncc\E[0;33mc\E[0;0m";
	char d[] = "\nddd";
	line->search_string = str_xcreate(0);
	
	/* str_xaddback(line->str, "\n", 1); */
	/* str_xaddback(line->str, REV_I_SEARCH_STR, ft_strlen(REV_I_SEARCH_STR)); */
	/* str_xaddback(line->str, "\naaaaaaaaa", 10); */
	str_xaddback(line->str, a, ft_strlen(a));
	str_xaddback(line->str, b, ft_strlen(b));
	str_xaddback(line->str, c, ft_strlen(c));
	str_xaddback(line->str, d, ft_strlen(d));
}
