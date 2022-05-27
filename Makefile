# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 11:04:05 by gufestin          #+#    #+#              #
#    Updated: 2022/05/27 18:47:58 by gufestin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c pipex.c ft_execve.c\
	ft_split.c ft_strjoin.c ft_strnstr.c

OBJS	= ${SRCS:.c=.o}

NAME	= pipex

CC	= cc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror


%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re: fclean all


.PHONY:		all clean fclean re
