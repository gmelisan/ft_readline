/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:29:42 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/11 16:58:24 by gmelisan         ###   ########.fr       */
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

static void init_line(t_line *line, char *prompt)
{
	ft_bzero(line, sizeof(t_line));
	line->str = str_xcopy(prompt);
	line->start = line->str.len;
	line->cpos = line->start;
}

static void init_bindings(t_vector *key_bindings)
{
	int i;

	*key_bindings = vec_create(0, sizeof(t_binding)); /* todo: vec_xcreate */
	bind(key_bindings, ARROW_LEFT, move_backward);
	bind(key_bindings, ARROW_RIGHT, move_forward);
	bind(key_bindings, CTRL_B, move_backward);
	bind(key_bindings, CTRL_F, move_forward);
	bind(key_bindings, BACKSPACE, backspace);
	bind(key_bindings, DEL, backspace);
	bind(key_bindings, CTRL_D, delete);
	bind(key_bindings, ENTER, self_insert);
	bind(key_bindings, CTRL_L, clear_screen);
	bind(key_bindings, CTRL_A, goto_start);
	bind(key_bindings, CTRL_E, goto_end);
	bind(key_bindings, CTRL_T, swap_chars);
	bind(key_bindings, TAB, self_insert);
	i = 32;
	while (ft_isprint(i))
		bind(key_bindings, i++, self_insert);
}

static void del(void *elem)
{
	str_delete(&((t_binding *)elem)->sequence);
}

static void	clear_bindings(t_vector *key_bindings)
{
	vec_delete(key_bindings, del);
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

void	perform_action(t_line *line, t_vector *key_bindings)
{
	t_binding	*b;

	b = find_binding(key_bindings, line->keybuf);
	if (b && b->action)
	{
		(*b->action)(line);
		update_line(line);
	}
}

int		is_ansiseq(char buf[KEYBUF_SIZE])
{
	if (buf[0] == ESC && (buf[1] == '[' || buf[1] == 'O'))
		return (1);
	return (0);
}

void	loginfo(t_line *line)
{
	char c;

	c = line->keybuf[0];
	ft_fdprintf(g_logfd, "-> (%c) [%d %d %d %d %d %d], str: \"%s\", pos = %d\n",
				ft_isprint(c) ? c : ' ', line->keybuf[0], line->keybuf[1], line->keybuf[2], line->keybuf[3],
				line->keybuf[4], line->keybuf[5], line->str.s, line->cpos);
}

int		input_loop(t_line *line, t_vector *key_bindings)
{
	int		ret;

	while ((ret = read(STDIN, line->keybuf, 1) > 0 && *line->keybuf != NL))
	{
		if (*line->keybuf == ESC)
		{
			if ((ret = read(STDIN, line->keybuf + 1, 1)) <= 0)
				break ;
			if (is_ansiseq(line->keybuf))
				if ((ret = read(STDIN, line->keybuf + 2, KEYBUF_SIZE - 3)) <= 0)
					break ;
		}
		if (*line->keybuf == CTRL_D && (int)line->str.len <= line->start)
			return (1);
		perform_action(line, key_bindings);
		loginfo(line);
		ft_bzero(line->keybuf, KEYBUF_SIZE);
	}
	if (ret < 0)
		g_errno = ERROR_READ;
	return (0);
}

/*
** If EOF, return NULL.
** If error, return NULL and raise g_errno.
*/

char	*ft_readline(char *prompt)
{
	t_line		line;
	t_vector	key_bindings;
	int			exit;

	sig_init();
	term_init();
	if (g_errno)
		return (NULL);
	term_setup();
	init_line(&line, prompt);
	init_bindings(&key_bindings);
	init_linebuf(line);
	update_line(NULL);
	exit = input_loop(&line, &key_bindings);
	clear_linebuf();
	clear_line(&line, exit);
	clear_bindings(&key_bindings);
	term_restore();
	return (line.str.s);
}
