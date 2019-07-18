/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 21:18:46 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/17 00:48:45 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	del(void *content, size_t size)
{
	if (size || !size)
		free(content);
}

void		history_load(t_history *history, char *path)
{
	int			fd;
	char		*str;
	int			ret;

	if (!path)
		return ;
	history->size = 0;
	history->path = path;
	if ((fd = open(path, O_RDONLY | O_CREAT, S_IRWXU)) < 0
		&& (g_errno = ERROR_OPENHIST))
		return ;
	while ((ret = get_next_line(fd, &str)) > 0)
	{
		ft_dlstaddback(&history->item, ft_dlstnew(str, ft_strlen(str) + 1));
		history->size++;
	}
	if (ret < 0)
		g_errno = ERROR_GNLHIST;
	while (history->size > HISTORY_MAXSIZE)
	{
		ft_dlstdelfront(&history->item, del);
		history->size--;
	}
	close(fd);
	return ;
}

void		history_clear(t_history *history)
{
	if (history)
	{
		ft_dlstdel(&history->item, del);
		free(history);
	}
}

static void	history_save(t_history *history, int fd, int append)
{
	if (append)
	{
		while (history->item->next)
			history->item = history->item->next;
		ft_fdprintf(fd, "%s\n", (char *)history->item->content);
	}
	else
	{
		while (history->item->prev)
			history->item = history->item->prev;
		while (history->item->next)
		{
			ft_fdprintf(fd, "%s\n", (char *)history->item->content);
			history->item = history->item->next;
		}
		ft_fdprintf(fd, "%s\n", (char *)history->item->content);
	}
}

void		history_push(t_history *history, char *str)
{
	int fd;
	int append;

	append = 1;
	if (*str == 0)
		return ;
	if (history->size >= HISTORY_MAXSIZE)
	{
		append = 0;
		ft_dlstdelfront(&history->item, del);
		history->size--;
	}
	fd = open(history->path,
				O_RDWR | (append ? O_APPEND : O_TRUNC) | O_CREAT, S_IRWXU);
	ft_dlstaddback(&history->item, ft_dlstnew(str, ft_strlen(str) + 1));
	history_save(history, fd, append);
	history->size++;
	close(fd);
}

