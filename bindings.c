/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:43:02 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/20 04:37:47 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"

static void del(void *elem)
{
	str_delete(&((t_binding *)elem)->sequence);
}

void	clear_bindings(t_vector *key_bindings)
{
	vec_delete(key_bindings, del);
}

static t_string get_sequence(int key)
{
	t_string str;

	str_zero(&str);
	if (key == ARROW_LEFT)
		str = str_xcopy(term_getstr("kl"));
	else if (key == ARROW_RIGHT)
		str = str_xcopy(term_getstr("kr"));
	else if (key == ARROW_UP)
		str = str_xcopy(term_getstr("ku"));
	else if (key == ARROW_DOWN)
		str = str_xcopy(term_getstr("kd"));
	else if (key == CTRL_LEFT)
		str = str_xcopy(CTRL_LEFT_SEQ);
	else if (key == CTRL_RIGHT)
		str = str_xcopy(CTRL_RIGHT_SEQ);
	else if (key == CTRL_UP)
		str = str_xcopy(CTRL_UP_SEQ);
	else if (key == CTRL_DOWN)
		str = str_xcopy(CTRL_DOWN_SEQ);
	else if (key == HOME)
		str = str_xcopy(term_getstr("kh"));
	else if (key == END)
		str = str_xcopy(term_getstr("@7"));
	else if (key == DELETE)
		str = str_xcopy(term_getstr("kD"));
	else if (key == INSERT)
		str = str_xcopy(term_getstr("kI"));
	else if (key)
	{
		str = str_xcreate(1);
		str.s[0] = (char)key;
	}					
	return (str);
}

void	bind(t_vector *key_bindings, int key, f_action action)
{
	t_binding new;

	new.key = key;
	new.action = action;
	new.sequence = get_sequence(key);
	vec_xaddback(key_bindings, &new); /* todo: vec_xaddback */
	/* todo: check for duplicates */
}

t_binding	*find_binding(t_vector *key_bindings, char *buf)
{
	int			i;
	t_binding	*b;

	i = 0;
	while (i < (int)key_bindings->len)
	{
		b = (t_binding *)vec_get(*key_bindings, i);
		if (ft_strequ(b->sequence.s, buf))
			return (b);
		i++;
	}
	return (NULL);
}

/*
**  key					termcap			terminfo		sequence
** --------------------------------------------------------------
** app_mode on			ks				smkx			\E[?1h\E=
** app_mode off			ke				rmkx			\E[?1l\E>
** 
** arrow_left			kl				kcub1			\EOD
** arrow_right			kr				kcuf1			\EOC
** arrow_up				ku				kcuu1			\EOA
** arrow_down			kd				kcud1			\EOB
**
** go_left				le				cub1			\b
** go_right				nd				cuf1			\E[C
** go_up				up				cuu1			\E[A
** go_down				do				cud1			\n
**
** delete				kD				kdch1			\E[3~
** insert				kI				kich1			\E[2~
** home					kh				khome			\EOH
** end					@7				kend			\EOF
**
** save cursor pos		sc				sc				\E7
** restore cursor pos	rc				rc				\E8	
*/
