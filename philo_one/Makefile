# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/04 18:47:11 by alicetetu         #+#    #+#              #
#    Updated: 2020/11/07 19:02:53 by alicetetu        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		philo_one

SRCS =		main.c \
			error.c \
			exit.c \
			init.c \
			messages.c \
			philo_actions.c \
			routines.c \
			threads.c \
			utils.c \
			utils_2.c 

OBJS = 		$(SRCS:.c=.o)

CC =		clang

RM = 		rm -f

CFLAGS = 	-Wall -Wextra -Werror

COMPILE	=	$(CC) $(FLAGS) -I. 

all:		$(NAME)


$(NAME): 	$(OBJS)
			$(COMPILE) -pthread $(OBJS) -o $(NAME)

clean:		
			${RM} ${OBJS}
		
fclean: 	clean
			${RM} ${NAME}
		
re:			fclean all

.PHONY: 	fclean clean all re
