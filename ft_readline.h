/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:35:39 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/16 23:19:57 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>

# include "libft.h"
# include "ft_string.h"
# include "ft_vector.h"

# include "xmalloc.h"
# include "str_xfuncs.h"
# include "vec_xfuncs.h"
# include "defs.h"
# include "ft_errno.h"
# include "line.h"
# include "terminal.h"
# include "keys.h"
# include "bindings.h"
# include "display.h"
# include "signal_handlers.h"
# include "actions.h"
# include "input_loop.h"
# include "history.h"

char	*ft_readline(char *prompt, t_history *history);

#endif
