/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:57:39 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/08 17:05:39 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	sigh_sigsegv(int sig)
{
	if (sig == SIGSEGV)
	{
		term_restore();
		ft_putstr("Segmentation fault.\n");
		ft_fdprintf(g_logfd, "Exit (Segmentation fault)\n");
		close(g_logfd);
		exit(1);
	}
}

void	sigh_sigabrt(int sig)
{
	if (sig == SIGABRT)
	{
		term_restore();
		ft_putstr("Aborted.\n");
		ft_fdprintf(g_logfd, "Exit (Abort)\n");
		close(g_logfd);
		exit(1);
	}
}

void	sigh_sigint(int sig)
{
	
	if (sig == SIGINT)
	{
		term_restore();
		ft_putstr("^C\n");
		ft_fdprintf(g_logfd, "Exit (CTRL+C)\n");
		close(g_logfd);
		exit(1);
	}
}

void	sigh_sigwinch(int sig)
{
	if (sig == SIGWINCH)
		update_line(NULL);
}
