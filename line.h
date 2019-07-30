/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:10:45 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/30 05:48:58 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include "defs.h"
# include "history.h"

typedef struct		s_line
{					
	t_string		*str;			/* shortcut for history->item->content */
	char			*result;		/* what we return */
	t_string		prompt;	
	int				cpos;			/* relative to `str' */
	char			keybuf[KEYBUF_SIZE];
	int				overwrite_mode;
	int				hs_mode;
	struct			s_hs
	{
		t_string	query;
		t_string	original_str;
		int			original_cpos;
		char		*pos;
		t_dlist		*start;
		int			fail;
	}				hs;
	int				vi_mode;	/* TODO: vi */
	t_string		kill_buffer;
	t_history		*history;
	t_history		*history_orig;
	t_list			*changes;		/* TODO: undo */
}					t_line;

#endif
