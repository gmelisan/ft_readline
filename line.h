/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:10:45 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/06 20:35:36 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

typedef struct	s_line
{
	t_string	str;
	int			start;
	int			cpos;
	char		keybuf[KEYBUF_SIZE];
	t_list		*history;
	t_list		*changes;
}				t_line;

#endif
