# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:08:14 by mcauchy-          #+#    #+#              #
#    Updated: 2025/03/18 11:31:40 by mcauchy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./srcs/action.c ./srcs/init.c ./srcs/monitoring.c ./srcs/utils.c ./srcs/check.c ./srcs/main.c

HEADER	=	include/philo.h

NAME	=	philo

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3

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