/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_search_history.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:37:14 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/28 20:05:00 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	reverse_search_history(t_line *line)
{
	line->search_string = str_xcreate(0);
	line->search_mode = 1;
}
