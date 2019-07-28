/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:29:42 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/28 20:24:48 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_line *g_line;

static void	sig_init(void)
{
	signal(SIGINT, sigh_sigint);
	signal(SIGSEGV, sigh_sigsegv);
	signal(SIGABRT, sigh_sigabrt);
	signal(SIGWINCH, sigh_sigwinch);
}

static void init_line(t_line *line, char *prompt, t_history **history)
{
	t_string temp_str;

	ft_bzero(line, sizeof(t_line));
	line->history_orig = *history;
	line->history = history_copy(*history);
	temp_str = str_xcreate(0);
	history_push(line->history, temp_str);
	line->str = (t_string *)line->history->item->content;
	g_line = line;
	line->prompt = str_xcopy(prompt);
}

static void	clear_line(t_line *line, int exit, t_history **history)
{
	line->result = ft_strdup(line->str->s);
	history_save(line->history_orig, line->str);
	history_clear(line->history);
	*history = line->history_orig;
	str_delete(&line->prompt);
	str_delete(&line->kill_buffer);
	if (exit)
	{
		ft_printf("exit");
		ft_strdel(&line->result);
	}
	/* clear undo stack */
}

/*
** If EOF, return NULL.
** If error, return NULL and raise g_errno.
*/

char	*ft_readline(char *prompt, t_history **history)
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
	init_linebuf(&line);
	update_line(NULL);
	exit = input_loop(&line, &key_bindings);
	clear_linebuf();
	clear_line(&line, exit, history);
	clear_bindings(&key_bindings);
	term_restore();
	return (line.result);
}
