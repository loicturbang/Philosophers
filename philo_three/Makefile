# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 15:33:30 by user42            #+#    #+#              #
#    Updated: 2021/02/17 13:55:35 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(addprefix srcs/, philo_three.c print.c parsing.c ft_time.c \
				philo.c monitoring.c init_threads.c sem_utils.c)
UTILS		= $(addprefix srcs/utils/, utils.c ft_atoi.c ft_itoa.c \
				ft_strjoin.c ft_lst.c ft_free.c ft_write.c)

PHILO		=  $(SRCS)			\
			   $(UTILS)			\

OBJS		= ${PHILO:.c=.o}

NAME		= philo_three

CC			= gcc -pthread

INCLUDES	= ./includes/

CFLAGS		= -Wall -Werror -Wextra -I ${INCLUDES}

RM			= rm -f

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		clean fclean re all
