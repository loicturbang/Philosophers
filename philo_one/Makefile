SRCS		= philo_one.c

OBJS		= ${SRCS:.c=.o}

NAME		= philo_one

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra

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
