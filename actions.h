/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:51:08 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/11 03:11:30 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "ft_readline.h"

void	self_insert(t_line *line);
void	backspace(t_line *line);
void	delete(t_line *line);
void	move_forward(t_line *line);
void	move_backward(t_line *line);
void	history_prev(t_line *line);
void	history_next(t_line *line);
void	undo(t_line *line);
void	clear_screen(t_line *line);
void	goto_start(t_line *line);
void	goto_end(t_line *line);
void	swap_chars(t_line *line);

#endif
