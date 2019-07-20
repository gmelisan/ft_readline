/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:10:45 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/20 07:34:12 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include "defs.h"
# include "history.h"

typedef struct	s_line
{
	t_string	*str;			/* shortcut for history->item->content */
	char		*result;		/* what we return */
	t_string	prompt;
	int			cpos;			/* relative to `str' */
	char		keybuf[KEYBUF_SIZE];
	int			overwrite_mode;
	t_string	kill_buffer;
	t_history	*history;
	t_history	*history_orig;
	t_list		*changes;		/* todo: */
}				t_line;

#endif
