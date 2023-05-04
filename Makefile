# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonjo <hyeonjo@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 14:51:34 by hyeonjo           #+#    #+#              #
#    Updated: 2023/05/03 15:03:47 by hyeonjo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra

NAME = minishell

SRCS = minishell.c \
	   ./parse/check_argument.c \
	   ./parse/ft_split_arg.c \
	   ./parse/join_string.c \
	   ./parse/parse.c \
	   ./parse/quotes_setting.c \
	   ./parse/tokenize_util.c \
	   ./parse/tokenize.c \
	   ./utilites/print_error.c \
	   ./utilites/exit_errno.c \
	   ./utilites/file_open_check.c \
	   ./utilites/init_cmd_and_free_utils.c \
	   ./utilites/signal_handle.c \
	   ./utilites/handle_error_syscall.c \
	   ./utilites/handle_error_syscall2.c \
	   ./utilites/utils1.c \
	   ./utilites/utils2.c \
	   ./utilites/utils3.c \
	   ./utilites/utils4.c \
	   ./utilites/utils5.c \
	   ./env/env_utils.c \
	   ./env/env_utils2.c \
	   ./execute/execute.c \
	   ./execute/execute_sub.c \
	   ./execute/check_valid_syntex.c \
	   ./execute/close_unused_fd.c \
	   ./execute/execute_utils.c \
	   ./execute/heredoc.c \
	   ./execute/heredoc_sub.c \
	   ./execute/heredoc_utils.c \
	   ./execute/io_file_open.c \
	   ./execute/path.c \
	   ./execute/redirection.c \
	   ./execute/tmp_file.c \
	   ./execute/wait_child.c \
	   ./builtins/builtins_utils.c \
	   ./builtins/cd.c \
	   ./builtins/echo.c \
	   ./builtins/env.c \
	   ./builtins/exit.c \
	   ./builtins/pwd.c \
	   ./builtins/unset.c \
	   ./builtins/export.c \
	   ./builtins/export_util.c

OBJS = $(SRCS:%.c=%.o)

READLINE_LIB 	= -lreadline -L${HOME}/goinfre/.brew/opt/readline/lib
READLINE_INC	= -I${HOME}/goinfre/.brew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY:	all clean fclean re
