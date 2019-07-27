/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:54:13 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/26 21:31:35 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int		g_logfd;

int		main(void)
{
	int			exit_flag;
	char		*res;
	t_string	prompt;
	t_history	*history;

	exit_flag = 0;
	history = ft_xmemalloc(sizeof(*history));
	history_load(history, DEFAULT_HIST_PATH);
	g_logfd = open("./log", O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
	ft_fdprintf(g_logfd, "Start\n");
	/* prompt = str_xcopy("readline # "); */
	prompt = str_xcopy("\E[0;31mreadline #\E[m ");
	while (42)
	{
		res = ft_readline(prompt.s, &history);
		if (!res)
			break ;
		if (g_errno)
			printerr();
		else
			ft_printf("-> \"%s\"\n", res);
		ft_strdel(&res);
	}
	str_delete(&prompt);
	ft_fdprintf(g_logfd, "End\n");
	close(g_logfd);
	history_clear(history);
	return (0);
}
