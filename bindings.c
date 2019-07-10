/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:43:02 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/08 14:26:04 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"

static t_string get_sequence(int key)
{
	t_string str;

	if (key == ARROW_LEFT)
		str = str_xcopy(term_getstr("kl"));
	else if (key == ARROW_RIGHT)
		str = str_xcopy(term_getstr("kr"));
	else if (key == ARROW_UP)
		str = str_xcopy(term_getstr("ku"));
	else if (key == ARROW_DOWN)
		str = str_xcopy(term_getstr("kd"));
	else if (key == CTRL_LEFT)
		str = str_xcopy(CTRL_LEFT_SEQ);
	else if (key == CTRL_RIGHT)
		str = str_xcopy(CTRL_RIGHT_SEQ);
	else if (key == CTRL_UP)
		str = str_xcopy(CTRL_UP_SEQ);
	else if (key == CTRL_DOWN)
		str = str_xcopy(CTRL_DOWN_SEQ);
	else if (key)
	{
		str = str_xcreate(1);
		str.s[0] = (char)key;
	}
	else
		str_zero(&str);
						
	return (str);
}

void	bind(t_vector *key_bindings, int key, f_action action)
{
	t_binding *new;

	new = ft_xmemalloc(sizeof(*new));
	new->key = key;
	new->action = action;
	new->sequence = get_sequence(key);
	vec_addback(key_bindings, (void *)new); /* todo: vec_xaddback */
	/* todo: check for duplicates */
}

t_binding	*find_binding(t_vector *key_bindings, char *buf)
{
	int			i;
	t_binding	*b;

	i = 0;
	while (i < (int)key_bindings->len)
	{
		b = (t_binding *)vec_get(*key_bindings, i);
		if (ft_strequ(b->sequence.s, buf))
			return (b);
		i++;
	}
	return (NULL);
}
