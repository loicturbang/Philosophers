# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 15:33:30 by user42            #+#    #+#              #
#    Updated: 2021/01/27 17:15:41 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(addprefix srcs/, philo_one.c print.c utils.c parsing.c \
				ft_atoi.c)

OBJS		= ${SRCS:.c=.o}

NAME		= philo_one

CC			= gcc

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
