/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bindings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 18:06:44 by gmelisan          #+#    #+#             */
/*   Updated: 2019/08/02 18:09:50 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"

static void del(void *elem)
{
	str_delete(&((t_binding *)elem)->sequence);
}

void	clear_bindings(t_vector *key_bindings)
{
	vec_delete(key_bindings, del);
}
