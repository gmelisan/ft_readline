/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:34:02 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/15 16:43:57 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDINGS_H
# define BINDINGS_H

# include "ft_readline.h"
# include "line.h"

typedef void (*f_action)(t_line *line);

typedef struct	s_binding
{
	enum e_key	key;
	t_string	sequence;
	f_action	action;
}				t_binding;

void		bind(t_vector *key_bindings, int key,  f_action action);
t_binding	*find_binding(t_vector *key_bindings, char *buf);
void		init_bindings(t_vector *key_bindings);
void		clear_bindings(t_vector *key_bindings);

#endif
