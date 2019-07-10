/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:35:39 by gmelisan          #+#    #+#             */
/*   Updated: 2019/07/08 17:05:57 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
/* # include <sys/stat.h> */
# include <sys/ioctl.h>

# include "libft.h"
# include "ft_string.h"
# include "ft_vector.h"

# include "xmalloc.h"
# include "str_xfuncs.h"
# include "defs.h"
# include "ft_errno.h"
# include "line.h"
# include "terminal.h"
# include "keys.h"
# include "bindings.h"
# include "display.h"

extern int	g_logfd;

char	*ft_readline(char *prompt);

#endif
