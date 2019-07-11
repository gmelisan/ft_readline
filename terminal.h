/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 10:54:51 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/11 18:48:57 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <unistd.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <termios.h>

# include "ft_readline.h"

# define DEFAULT_TERMTYPE	"dumb"
# define TERM_BUFFER		2048
# define KEY_BUF			32
# define ONECAP_BUFFER		32

char	*term_getstr(char *str);
void	term_putstr(char *str);
void	term_init(void);
void	term_setup(void);
void	term_restore(void);

void	term_getpos(int *row, int *col);

extern struct termios	g_init_tios;

#endif
