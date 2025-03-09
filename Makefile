SRCS	=	action.c init.c monitoring.c routine.c utils.c

HEADER	=	./include/philo.h

NAME	=	philo

OBJS	=	$(SRCS.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

$(NAME)	:	$(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all		:	$(NAME)

%.c		:	%.o
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all