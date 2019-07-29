/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:13:31 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/29 04:49:58 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "terminal.h"
#include "escseqs.h"

t_buffer		g_buffer;

static int		max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int				get_screenwidth(void)
{
	return (g_buffer.out_cols);
}

/*
** In fact we don't need to go to start. May be fix later.
*/

static void		move_cur_start(void)
{
	int crow;
	int ccol;
	int i;

	crow = g_buffer.cpos / g_buffer.out_cols;
	ccol = g_buffer.cpos % g_buffer.out_cols;
	i = -1;
	while (++i < crow)
		term_putstr("up");
	/* i = -1; */
	/* while (++i < ccol) */
	/* 	term_putstr("le"); */
	term_putstr("cr");
}

static  void		move_cur_right(int oldpos, int width)
{
	int	oldccol;

	oldccol = oldpos % width;
	if (oldccol == width - 1)
	{
		term_putstr("do");
		term_putstr("cr");
	}
	else
		term_putstr("nd");
}

static void		move_cur_left(int oldpos, int width)
{
	int	oldccol;
	int	i;

	oldccol = oldpos % width;
	if (oldccol == 0)
	{
		term_putstr("up");
		i = -1;
		while (++i < width - 1)
			term_putstr("nd");
	}
	else
		term_putstr("le");
}

static t_string	*build_bufout(t_string str, int width)
{
	int			rows;
	t_string	*res;
	int			i;
	int			j;

	rows = str.len / width + 1;
	res = ft_xmemalloc(sizeof(t_string) * (rows + 1));
	i = -1;
	while (++i < rows)
	{
		res[i] = str_xcreate(width);
		j = -1;
		while (++j < (int)res[i].len)
			res[i].s[j] = str_get(str, width * i + j);
		str_fixlen(res + i);
	}
	return (res);
}

/*
** Count how many times we need to step in inner loop of redisplay.
** We need this checks when resizing.
** Also we get maximum value of old and new buf's lens because
** when our new buffer is lesser then old, we need to clear
** remainings from old.
*/

static int		cols(t_buffer *newbuf, int i)
{
	t_string	*old;
	t_string	*new;
	int			newlen;
	int			oldlen;

	old = (i < newbuf->out_rows && i >= 0 ? &newbuf->out[i] : NULL);
	new = (i < g_buffer.out_rows && i >= 0 ? &g_buffer.out[i] : NULL);
	oldlen = old ? old->len : 0;
	newlen = new ? new->len : 0;
	return (max(oldlen, newlen));
}

static void		print(t_buffer *newbuf, int pos)
{
	t_escseq	*es;

	if ((es = find_escseq(newbuf->escseqs, pos)))
		ft_fdprintf(STDOUT, "%s", es->str.s);
	if (str_get(newbuf->b, pos))
		ft_fdprintf(STDOUT, "%c", str_get(newbuf->b, pos));
	else
		ft_fdprintf(STDOUT, " ");
}

/*
** Main redisplay loop. Now it just redraw all characters, even 
** if they are the same.
** TODO: skip repeated characters.
*/

static  void	redisplay(t_buffer *newbuf, int resize)
{
	int i;
	int j;
	int pos;

	move_cur_start();
	i = -1;
	pos = 0;
	while (++i < max(newbuf->out_rows, g_buffer.out_rows))
	{
		j = -1;
		while (++j < cols(newbuf, i))
		{
			print(newbuf, pos);
			if (pos % newbuf->out_cols == newbuf->out_cols - 1)
				move_cur_right(pos, newbuf->out_cols);
			pos++;
		}
	}
	if (resize)
		term_putstr("cd");	/* "ce" for linux. Should be at col 0. Fix later */	
	while (pos != newbuf->cpos)
		move_cur_left(pos--, newbuf->out_cols);
}

void	init_linebuf(t_line *line)
{
	struct winsize	ws;

	ioctl(STDOUT, TIOCGWINSZ, &ws);
	g_buffer.b = str_xduplicate(line->prompt);
	g_buffer.original = str_xduplicate(g_buffer.b);
	pull_escseqs(&g_buffer.escseqs, &g_buffer.b);
	g_buffer.prompt_len = g_buffer.b.len;
	g_buffer.cpos = g_buffer.prompt_len;
	g_buffer.out_rows = g_buffer.b.len / ws.ws_col + 1;
	g_buffer.out_cols = ws.ws_col;
	g_buffer.out = build_bufout(g_buffer.b, ws.ws_col);
}

static void	del(void *str)
{
	str_delete(str);
}

void	clear_linebuf(void)
{
	str_delarr(&g_buffer.out);
	str_delete(&g_buffer.b);
	vec_delete(&g_buffer.escseqs, del);
	str_delete(&g_buffer.original);
	ft_bzero(&g_buffer, sizeof(t_buffer));
}

void	convert_nl(t_buffer *buf, int width)
{
	int	i;
	int j;
	int	add;
	int from;

	add = 0;
	i = -1;
	from = 0;
	while (str_get(buf->b, ++i))
	{
		if (str_get(buf->b, i) == '\n')
		{
			/* add = count_escseq(buf->escseqs, from, i); */
			add = (width - (i % width)) - 1;
			from = i;
			shift_escseq(&buf->escseqs, from, add);
			buf->b.s[i] = ' ';
			j = 0;
			while (++j < (width - (i % width)))
				str_xinsert(&buf->b, i, " ", 1);
		}
	}
}

/*
** Idea as in the original Readline lib.
** Two buffers: 
** - `g_buffer' is what on the screen now.
** - `newbuf' builded from `line', what we want our screen to be.
** We update screen using `newbuf' and in the end put its contents
** to `g_buffer'.
*/

void	update_line(t_line *line)
{
	t_buffer		newbuf;
	struct winsize	ws;

	ioctl(STDOUT, TIOCGWINSZ, &ws);
	if (line)
	{
		newbuf.original = str_xduplicate(*line->str);
		str_xaddfront(&newbuf.original, line->prompt.s, line->prompt.len);
		newbuf.b = str_xduplicate(newbuf.original);
	}
	else
	{
		newbuf.b = str_xduplicate(g_buffer.original);
		newbuf.original = str_xduplicate(g_buffer.original);
	}
	pull_escseqs(&newbuf.escseqs, &newbuf.b);
	convert_nl(&newbuf, ws.ws_col);
	newbuf.cpos = (line ? g_buffer.prompt_len + line->cpos : g_buffer.cpos);
	newbuf.prompt_len = g_buffer.prompt_len;
	newbuf.out_rows = newbuf.b.len / ws.ws_col + 1;
	newbuf.out_cols = ws.ws_col;
	newbuf.out = build_bufout(newbuf.b, ws.ws_col);
	redisplay(&newbuf, line ? 0 : 1);
	clear_linebuf();
	ft_memcpy(&g_buffer, &newbuf, sizeof(t_buffer));
}
