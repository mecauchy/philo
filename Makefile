SRCS	=	./srcs/action.c ./srcs/init.c ./srcs/monitoring.c ./srcs/routine.c ./srcs/utils.c ./srcs/check.c ./srcs/main.c

HEADER	=	include/philo.h

NAME	=	philo

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

$(NAME)	:	$(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "Compilation done"

all		:	$(NAME)

%.c		:	%.o

clean	:
			rm -rf $(OBJS)
			@echo "Objects deleted"

fclean	:	clean
			rm -rf $(NAME)
			@echo "Executable deleted"

re		:	fclean all