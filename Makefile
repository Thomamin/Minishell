# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shane <shane@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 13:03:55 by youngjpa          #+#    #+#              #
#    Updated: 2023/04/10 11:39:22 by shane            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS		=	minishell.c				 \
				testforder.c			 \
				./parse/arg_check.c 	 \
				./parse/ft_split_arg.c   \
				./parse/join_string.c    \
				./parse/parse.c 		 \
				./parse/quotes_setting.c \
				./parse/tokenize_util.c  \
				./parse/tokenize.c		 \
				./utilites/exit_errono.c \
				./utilites/file_open_check.c\
				./utilites/init_and_free.c \
				./utilites/signal_handle.c \
				./utilites/systemcall2.c \
				./utilites/utils1.c \
				./utilites/utils2.c \
				./utilites/utils3.c \
				./utilites/utils4.c \
				./utilites/utils5.c \
				./env/env_utils.c	\
				./env/env_utils2.c

OBJS		= $(SRCS:%.c=%.o)

CC = gcc $(DEBUG)
CFLAGS = 
#-Werror -Wall -Wextra
# SAN = -fsanitize=address -g3
DEBUG = -g
READLINE_LIB 	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include
# READLINE_LIB 	= -lreadline -L${HOME}/.brew/opt/readline/lib
# READLINE_INC	= -I${HOME}/.brew/opt/readline/include

FT_DIR	= ./libft
FT 	= ft

all			:	$(NAME)

$(NAME)		:	$(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean		:
		rm -f $(OBJS)

fclean		:	clean
		rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re bonus
