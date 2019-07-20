/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backward_delete_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 07:10:58 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/20 07:11:12 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	backward_delete_char(t_line *line)
{
	if (line->cpos > 0)
	{
		line->cpos--;
		str_remove(line->str, line->cpos, 1);
	}
}
