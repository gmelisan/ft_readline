/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:28:08 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/18 04:34:36 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "ft_readline.h"

typedef struct	s_out
{
	t_string	*b;
	int			rows;
	int			cols;
}				t_out;

typedef struct	s_buffer
{
	t_string	b;
	int			cpos;
	t_out		out;
}				t_buffer;

extern t_buffer	g_buffer;

void			init_linebuf(t_line *line);
void			clear_linebuf(void);
void			update_line(t_line *line);
int				get_screenwidth(void);

#endif
/* line -> buffer, buf -> b */
