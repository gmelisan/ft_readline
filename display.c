/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:13:31 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/10 23:13:20 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "terminal.h"

t_buffer		g_buffer;

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

static  void		move_cur_right(int oldpos)
{
	int	oldccol;

	oldccol = oldpos % g_buffer.out.cols;
	if (oldccol == g_buffer.out.cols - 1)
	{
		term_putstr("do");
		term_putstr("cr");
	}
	else
		term_putstr("nd");
}

static void		move_cur_left(int oldpos)
{
	int	oldccol;
	int	i;

	oldccol = oldpos % g_buffer.out.cols;
	if (oldccol == 0)
	{
		term_putstr("up");
		i = -1;
		while (++i < g_buffer.out.cols - 1)
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

static int		max(int a, int b)
{
	return (a > b ? a : b);
}

static  void	redisplay(t_buffer newbuf)
{
	int i;
	int j;
	int pos;

	move_cur_start();
	i = -1;
	pos = 0;
	while (++i < newbuf.out.rows)
	{
		j = -1;
		while (++j < max(newbuf.out.b[i].len, g_buffer.out.b[i].len))
		{
			if (str_get(newbuf.out.b[i], j))
				ft_putchar(str_get(newbuf.out.b[i], j));
			else
				ft_putchar(' ');
			if (pos % newbuf.out.cols == newbuf.out.cols - 1)
				move_cur_right(pos);
			pos++;
		}
	}
	while (pos != newbuf.cpos)
		move_cur_left(pos--);	
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
	redisplay(newbuf);
	clear_linebuf();
	ft_memcpy(&g_buffer, &newbuf, sizeof(t_buffer));
}
