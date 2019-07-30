/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:57:39 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/30 16:44:53 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handlers.h"
#include "execinfo.h"

static void	log_backtrace(void)
{
	int		size;
	void	*bt_buffer[BT_BUFSIZE];

	size = backtrace(bt_buffer, BT_BUFSIZE);
	ft_fdprintf(g_logfd, "Backtrace:\n");
	backtrace_symbols_fd(bt_buffer, size, g_logfd);
}

void	sigh_sigsegv(int sig)
{
	if (sig == SIGSEGV)
	{
		term_restore();
		ft_putstr("Segmentation fault.\n");
		ft_fdprintf(g_logfd, "Exit (Segmentation fault)\n");
		log_backtrace();
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
		log_backtrace();
		close(g_logfd);
		exit(1);
	}
}

void	sigh_sigint(int sig)
{
	
	if (sig == SIGINT)
	{
		ft_putstr("^C");
		/* str_delete(g_line->str); */
		/* *g_line->str = str_xcreate(0); */
		/* g_line->hs_mode = 0; */
		/* g_line->cpos = 0; */
		reset_line(g_line);
		update_line(g_line);
		ft_fdprintf(g_logfd, "[CTRL+C]\n");
	}
}

void	sigh_sigwinch(int sig)
{
	if (sig == SIGWINCH)
	{
		update_line(NULL);
	}
}
