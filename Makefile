#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmelisan </var/spool/mail/vladimir>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/05 21:52:47 by gmelisan          #+#    #+#              #
#    Updated: 2019/07/06 22:09:29 by gmelisan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = readline

LIBFT = ./libft

CC = clang
CFLAGS = -Wall -Wextra
CFLAGS += -g

OBJ = main.o terminal.o ft_readline.o ft_errno.o display.o signal_handlers.o \
xmalloc.o str_xfuncs1.o str_xfuncs2.o bindings.o actions.o

all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(LIBFT) -lcurses -lft

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT)/include -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

