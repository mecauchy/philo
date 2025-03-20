# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:08:14 by mcauchy-          #+#    #+#              #
#    Updated: 2025/03/20 12:51:56 by mcauchy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	./srcs/action.c ./srcs/init.c ./srcs/monitoring.c \
				./srcs/utils.c ./srcs/check.c ./srcs/main.c

HEADER		=	include/philo.h

NAME		=	philo

OBJS		=	$(patsubst ./srcs/%.c,$(OBJS_DIR)%.o,$(SRCS))

OBJS_DIR	=	objs/

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

THREADFLAG	=	-pthread

$(NAME)		:	$(OBJS_DIR) $(OBJS)
				$(CC) $(CFLAGS) -I include $(OBJS) -o $(NAME)
				@echo "Compilation done"

$(OBJS_DIR)	:
				mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o	:	./srcs/%.c
	$(CC) $(CFLAGS) $(THREADFLAG) -I ./include -c $< -o $@

all			:	$(NAME)

clean		:
				rm -rf $(OBJS_DIR)
				@echo "Objects deleted"

fclean		:	clean
				rm -rf $(NAME)
				@echo "Executable deleted"

re			:	fclean all