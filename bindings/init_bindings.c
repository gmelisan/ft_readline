/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bindings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:58:51 by gmelisan          #+#    #+#             */
/*   Updated: 2019/08/01 06:00:49 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"

static void	init_bindings1(t_vector *key_bindings)
{
	bind(key_bindings, ARROW_LEFT, backward_char);
	bind(key_bindings, ARROW_RIGHT, forward_char);
	bind(key_bindings, ARROW_UP, previous_history);
	bind(key_bindings, ARROW_DOWN, next_history);
	bind(key_bindings, CTRL_P, previous_history);
	bind(key_bindings, CTRL_N, next_history);
	bind(key_bindings, CTRL_LEFT, backward_word);
	bind(key_bindings, CTRL_RIGHT, forward_word);
	bind(key_bindings, CTRL_UP, backward_line);
	bind(key_bindings, CTRL_DOWN, forward_line);
	bind(key_bindings, CTRL_B, backward_char);
	bind(key_bindings, CTRL_F, forward_char);
	bind(key_bindings, BACKSPACE, backward_delete_char);
	bind(key_bindings, DEL, backward_delete_char);
	bind(key_bindings, CTRL_D, delete_char);
	bind(key_bindings, DELETE, delete_char);
	bind(key_bindings, CTRL_A, beginning_of_line);
	bind(key_bindings, HOME, beginning_of_line);
	bind(key_bindings, END, end_of_line);
	bind(key_bindings, INSERT, overwrite_mode);
	bind(key_bindings, CTRL_E, end_of_line);
	/* bind(key_bindings, TAB, self_insert); */
	bind(key_bindings, ENTER, self_insert);
	bind(key_bindings, CTRL_L, clear_screen);
	bind(key_bindings, CTRL_T, transpose_chars);
	/* bind(key_bindings, ALT_T, transpose_words); */
}

static void init_bindings2(t_vector *key_bindings)
{
	bind(key_bindings, CTRL_K, kill_line);
	bind(key_bindings, CTRL_U, unix_line_discard);
	bind(key_bindings, CTRL_W, unix_word_rubout);
	bind(key_bindings, CTRL_Y, yank);
	bind(key_bindings, CTRL_R, reverse_search_history);
	bind(key_bindings, CTRL_G, reset_history_search);
}

void		init_bindings(t_vector *key_bindings)
{
	int i;

	*key_bindings = vec_xcreate(0, sizeof(t_binding));
	init_bindings1(key_bindings);
	init_bindings2(key_bindings);
	i = 32;
	while (ft_isprint(i))
		bind(key_bindings, i++, self_insert);
}
