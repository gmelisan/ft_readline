/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:13:31 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/18 04:47:10 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "terminal.h"

t_buffer		g_buffer;

static int		max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int				get_screenwidth(void)
{
	return (g_buffer.out.cols);
}

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
	return (max(oldlen, newlen));
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
	while (++i < max(newbuf->out.rows, g_buffer.out.rows))
	{
		j = -1;
		while (++j < cols(newbuf, i))
		{
			if (str_get(newbuf->b, pos))
				ft_fdprintf(STDIN, "%c", (str_get(newbuf->b, pos)));
			else
				ft_putchar(' ');
			if (pos % newbuf->out.cols == newbuf->out.cols - 1)
				move_cur_right(pos, newbuf->out.cols);
			pos++;
		}
	}
	if (resize)
		term_putstr("ce");
	while (pos != newbuf->cpos)
		move_cur_left(pos--, newbuf->out.cols);
}

void	init_linebuf(t_line *line)
{
	struct winsize	ws;

	ioctl(STDOUT, TIOCGWINSZ, &ws);
	g_buffer.b = str_xduplicate(*line->str);
	str_xaddfront(&g_buffer.b, line->prompt.s, line->prompt.len);
	g_buffer.cpos = line->prompt.len + line->cpos;
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
	t_buffer		newbuf;
	struct winsize	ws;

	ioctl(STDOUT, TIOCGWINSZ, &ws);
	if (line)
	{
		newbuf.b = str_xduplicate(*line->str);
		str_xaddfront(&newbuf.b, line->prompt.s, line->prompt.len);
	}
	else
		newbuf.b = str_xduplicate(g_buffer.b);
	newbuf.cpos = (line ? line->prompt.len + line->cpos : g_buffer.cpos);
	newbuf.out.rows = newbuf.b.len / ws.ws_col + 1;
	newbuf.out.cols = ws.ws_col;
	newbuf.out.b = build_bufout(newbuf.b, ws.ws_col);
	redisplay(&newbuf, line ? 0 : 1);
	clear_linebuf();
	ft_memcpy(&g_buffer, &newbuf, sizeof(t_buffer));
}
