NAME    := minishell
CFLAGS  := -Wall -Wextra -Werror -g -fsanitize=leak 
SRCS    := minishell.c
OBJS    := $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	cc  $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	cc	$(CFLAGS) -c $<	-o $@ 

clean:	
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY : all clean fclean re