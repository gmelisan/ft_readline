/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:28:08 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/26 22:35:12 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "ft_readline.h"

typedef struct	s_buffer
{
	t_string	original;
	t_string	b;
	t_vector	escseqs;
	int			cpos;
	int			prompt_len;
	t_string	*out;
	int			out_rows;
	int			out_cols;
}				t_buffer;

extern t_buffer	g_buffer;

void			init_linebuf(t_line *line);
void			clear_linebuf(void);
void			update_line(t_line *line);
int				get_screenwidth(void);

#endif
/* line -> buffer, buf -> b */
