/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:54:13 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/08 17:49:50 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int		g_logfd;

int		main(void)
{
	int			exit_flag;
	char		*res;
	t_string	prompt;

	exit_flag = 0;
	g_logfd = open("./log", O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
	ft_fdprintf(g_logfd, "Start\n");
	prompt = str_xcopy("readline # ");
	while (42)
	{
		res = ft_readline(prompt.s);
		if (!res)
			break ;
		if (g_errno)
			printerr();
		else
			ft_printf(" -> \"%s\"\n", res + prompt.len);
		ft_strdel(&res);
	}
	str_delete(&prompt);
	ft_fdprintf(g_logfd, "End\n");
	close(g_logfd);
	return (0);
}
