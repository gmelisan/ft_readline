/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escseqs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 23:43:11 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/27 00:12:16 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ESCSEQS_H
# define ESCSEQS_H

# include "ft_readline.h"

/* void	pull_escseqs(t_vector *vec, t_string *str, int width); */
t_string	get_escseq(t_string str, int *i);
void	pull_escseqs(t_vector *vec, t_string *str);

#endif
