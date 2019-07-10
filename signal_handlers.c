/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:57:39 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/11 00:06:13 by gmelisan         ###   ########.fr       */
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

void	output_buffer(int fd)
{
	int i;
	int j;

	ft_fdprintf(fd, "pos = %d\n", g_buffer.cpos);
	for (i = 0; i < g_buffer.out.rows; i++)
	{
		for (j = 0; j < (int)g_buffer.out.b[i].len; j++)
			ft_fdprintf(fd, "%c", str_get(g_buffer.out.b[i], j));
		ft_fdprintf(fd, "\n");
	}
}

void	sigh_sigwinch(int sig)
{
	struct winsize	ws;
	int fd_bufout;

	if (sig == SIGWINCH)
	{
		ioctl(STDOUT, TIOCGWINSZ, &ws);
		fd_bufout = open("./bufout", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
		ft_fdprintf(g_logfd, "[SIGWINCH] -> %dx%d\n", ws.ws_col, ws.ws_row);
		ft_fdprintf(fd_bufout, "before:\n");
		output_buffer(fd_bufout);
		ft_fdprintf(fd_bufout, "\n");
		update_line(NULL);
		
		ft_fdprintf(fd_bufout, "after:\n");
		output_buffer(fd_bufout);
		close(fd_bufout);
	}
}
