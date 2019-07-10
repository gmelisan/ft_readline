/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:13:31 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/11 02:55:40 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "terminal.h"

t_buffer		g_buffer;

/*
** In fact we don't need to go to start. May be fix later.
*/

static void		move_cur_start(void)
{
	int crow;
	int ccol;
	int i;

	crow = g_buffer.cpos / g_buffer.out.cols;
	ccol = g_buffer.cpos % g_buffer.out.cols;
	i = -1;
	while (++i < crow)
		term_putstr("up");
	i = -1;
	while (++i < ccol)
		term_putstr("le");
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

/* Not works. Now just using termcap("ce") instead. */

/* static void		clear_to_end(int pos, int width) */
/* { */
/* 	int i; */

/* 	i = pos % width - 1; */
/* 	while (++i < width) */
/* 		ft_putchar(' '); */
/* 	i--; */
/* 	while (i > pos) */
/* 		move_cur_left(i--, width); */
/* } */

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
** These checks are to be sure we are not out of buffer array when resizing.
*/

static char		getchar(t_buffer newbuf, int i, int j)
{
	if (newbuf.out.cols >= g_buffer.out.cols) /* screeen enlarge */
	{
		if (i < newbuf.out.rows && j < (int)newbuf.out.b[i].len)
			return (str_get(newbuf.out.b[i], j));
		else
			return (0);
	}
	else /* screen shrink */
	{
		if (i < g_buffer.out.rows && j < (int)g_buffer.out.b[i].len)
			return (str_get(g_buffer.out.b[i], j));
		else
			return (0);
	}
}

static t_string *get_outstr(t_buffer *buf, int i)
{
	if (i < buf->out.rows && i >= 0)
		return (&(buf->out.b[i]));
	return (NULL);
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

	old = get_outstr(newbuf, i);
	new = get_outstr(&g_buffer, i);
	oldlen = old ? old->len : 0;
	newlen = new ? new->len : 0;
	return (oldlen > newlen ? oldlen : newlen);
}

/*
** Main redisplay loop. Now it just redraw all characters, even 
** if they are the same.
** TODO: skip repeated characters.
*/

static  void	redisplay(t_buffer newbuf, int resize)
{
	int i;
	int j;
	int pos;

	move_cur_start();
	i = -1;
	pos = 0;
	while (++i < max(newbuf.out.rows, g_buffer.out.rows))
	{
		j = -1;
		while (++j < cols(&newbuf, i))
		{
			if (getchar(newbuf, i, j))
				ft_putchar(getchar(newbuf, i, j));
			else
				ft_putchar(' ');
			if (pos % newbuf.out.cols == newbuf.out.cols - 1)
				move_cur_right(pos, newbuf.out.cols);
			pos++;
		}
	}
	if (resize)
		term_putstr("ce");
	while (pos != newbuf.cpos)
		move_cur_left(pos--, newbuf.out.cols);
}

void	init_linebuf(t_line line)
{
	struct winsize	ws;

	ioctl(STDOUT, TIOCGWINSZ, &ws);
	g_buffer.b = str_xduplicate(line.str);
	g_buffer.cpos = line.cpos;
	g_buffer.out.rows = g_buffer.b.len / ws.ws_col + 1;
	g_buffer.out.cols = ws.ws_col;
	g_buffer.out.b = build_bufout(g_buffer.b, ws.ws_col);
}

void	clear_linebuf(void)
{
	str_delarr(&g_buffer.out.b);
	str_delete(&g_buffer.b);
	ft_bzero(&g_buffer, sizeof(t_buffer));
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
	t_buffer			newbuf;
	struct winsize	ws;

	ioctl(STDOUT, TIOCGWINSZ, &ws);
	newbuf.cpos = (line ? line->cpos : g_buffer.cpos);
	newbuf.b = str_xduplicate(line ? line->str : g_buffer.b);
	newbuf.out.rows = newbuf.b.len / ws.ws_col + 1;
	newbuf.out.cols = ws.ws_col;
	newbuf.out.b = build_bufout(newbuf.b, ws.ws_col);
	redisplay(newbuf, line ? 0 : 1);
	clear_linebuf();
	ft_memcpy(&g_buffer, &newbuf, sizeof(t_buffer));
}
