/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:58:25 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/30 01:36:04 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLERS_H
# define SIGNAL_HANDLERS_H

# include "ft_readline.h"

# define BT_BUFSIZE			32

void	sigh_sigsegv(int sig);
void	sigh_sigabrt(int sig);
void	sigh_sigint(int sig);
void	sigh_sigwinch(int sig);

extern int		g_logfd;
extern t_line	*g_line;

#endif
