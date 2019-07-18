/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:29:42 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/17 00:37:43 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	sig_init(void)
{
	signal(SIGINT, sigh_sigint);
	signal(SIGSEGV, sigh_sigsegv);
	signal(SIGABRT, sigh_sigabrt);
	signal(SIGWINCH, sigh_sigwinch);
}

static void init_line(t_line *line, char *prompt, t_history *history)
{
	ft_bzero(line, sizeof(t_line));
	line->str = str_xcopy(prompt);
	line->start = line->str.len;
	line->cpos = line->start;
	line->history = history;
}

static void	clear_line(t_line *line, int exit)
{
	if (exit)
	{
		str_delete(&line->str);
		ft_printf("exit");
	}
	/* clear undo stack */
}

/*
** If EOF, return NULL.
** If error, return NULL and raise g_errno.
*/

char	*ft_readline(char *prompt, t_history *history)
{
	t_line		line;
	t_vector	key_bindings;
	int			exit;

	sig_init();
	term_init();
	if (g_errno)
		return (NULL);
	term_setup();
	init_line(&line, prompt, history);
	init_bindings(&key_bindings);
	init_linebuf(line);
	update_line(NULL);
	exit = input_loop(&line, &key_bindings);
	history_push(history, line.str.s + line.start);
	clear_linebuf();
	clear_line(&line, exit);
	clear_bindings(&key_bindings);
	term_restore();
	return (line.str.s);
}
