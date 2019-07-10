/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 10:37:33 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/06 18:48:43 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

struct termios	g_init_tios;

static int	ft_putint(int c)
{
	write(STDOUT, &c, 1);
	return (0);
}

char		*term_getstr(char *str)
{
	static char	buf[ONECAP_BUFFER];
	char		**pb;

	ft_bzero(buf, ONECAP_BUFFER);
	pb = (char **)&buf;
	return (tgetstr(str, pb));
}

void		term_putstr(char *str)
{
	tputs(term_getstr(str), 1, ft_putint);
}

void		term_init(void)
{
	int			ret;
	char		*termtype;
	static char	term_buffer[TERM_BUFFER];
	int			needfree;

	needfree = 0;
	termtype = getenv("TERM");
	if (!termtype)
	{
		termtype = ft_xmemalloc(ft_strlen(DEFAULT_TERMTYPE) + 1);
		ft_strcpy(termtype, DEFAULT_TERMTYPE);
		needfree = 1;
	}
	ret = tgetent(term_buffer, termtype);
	if (needfree)
		free(termtype);
	if (ret < 0)
		g_errno = ERROR_TERMCAP;
	if (ret == 0)
		g_errno = ERROR_UNK_TERMTYPE;
}

void	term_setup(void)
{
	char *temp;
	struct termios work_tios;

	temp = term_getstr("pc");
	PC = temp ? *temp : 0;
	BC = term_getstr("le");
	UP = term_getstr("up");
	term_putstr("ks");

	tcgetattr(STDIN, &g_init_tios);
	work_tios = g_init_tios;
	work_tios.c_oflag &= ~OPOST;
	work_tios.c_lflag &= ~(ICANON | ECHO);
	work_tios.c_cc[VMIN] = 1;
	work_tios.c_cc[VTIME] = 0;
	tcsetattr(STDIN, TCSANOW, &work_tios);
	ospeed = work_tios.c_ospeed;
}

void	term_restore(void)
{
	tcsetattr(STDIN, TCSANOW, &g_init_tios);
	term_putstr("ke");
	ft_printf("\n");
}
