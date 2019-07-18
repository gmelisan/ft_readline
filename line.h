/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:10:45 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/18 02:56:03 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include "defs.h"
# include "history.h"

typedef struct	s_line
{
	t_string	str;			/* change everwhere to pointer */
	int			start;
	int			cpos;
	char		keybuf[KEYBUF_SIZE];
	int			overwrite_mode;
	t_history	*history;
	t_list		*changes;
}				t_line;

#endif
