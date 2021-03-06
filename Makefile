#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/05 21:52:47 by gmelisan          #+#    #+#              #
#    Updated: 2019/08/04 12:02:01 by gmelisan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = readline

LIBFT = ./libft

CC = clang
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g

OBJ = main.o terminal.o ft_readline.o ft_errno.o signal_handlers.o \
xmalloc.o str_xfuncs1.o str_xfuncs2.o input_loop.o vi_input_loop.o \
vec_xfuncs.o history.o escseqs.o history_search.o loginfo.o

OBJ += $(addprefix ./display/, \
update_line.o redisplay.o init_linebuf.o clear_linebuf.o move_cursor.o \
)

OBJ += $(addprefix ./bindings/, \
bindings.o bind.o bind_keys.o vi_bind_keys.o \
)

OBJ += $(addprefix ./actions/, \
self_insert.o backward_delete_char.o delete_char.o \
forward_char.o backward_char.o forward_word.o backward_word.o \
forward_line.o backward_line.o \
clear_screen.o overwrite_mode.o\
beginning_of_line.o end_of_line.o \
transpose_chars.o transpose_words.o \
previous_history.o next_history.o \
kill_line.o unix_line_discard.o unix_word_rubout.o yank.o \
reverse_search_history.o reset_history_search.o reset_line.o \
)

all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(LIBFT) -lcurses -lft

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT)/include -c -o $@ $<

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

$(OBJ): $(LIBFT)/include/libft.h *.h

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)/libft.a

re: fclean all
