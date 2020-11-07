# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/04 18:47:11 by alicetetu         #+#    #+#              #
#    Updated: 2020/11/06 17:10:05 by alicetetu        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		philo_three

SRCS =		main.c \
			check_args.c \
			clear.c \
			exit.c \
			init.c \
			messages.c \
			monitor.c \
			philo_actions.c \
			process.c \
			routines.c \
			time.c \
			threads.c \
			utils.c \
			utils_2.c

OBJS = 		$(SRCS:.c=.o)

CC =		gcc

RM = 		rm -f

CFLAGS = 	-Wall -Wextra -Werror -g3

COMPILE	=	$(CC) $(FLAGS) -I. 

all:		$(NAME)


$(NAME): 	$(OBJS)
			$(COMPILE) $(OBJS) -o $(NAME)

clean:		
			${RM} ${OBJS}
		
fclean: 	clean
			${RM} ${NAME}
		
re:			fclean all

.PHONY: 	fclean clean all re
