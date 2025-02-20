# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leothoma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:22:30 by leothoma          #+#    #+#              #
#    Updated: 2024/12/16 16:22:30 by leothoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = xd

COMP = cc

#FLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -03

SRC =	main.c \


OBJS = ${SRC:.c=.o}

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

#a%.o: %.c
#	$(CC) $(FLAGS) -c $< -o $@

#${NAME}: ${OBJS}
#	$(CC) $(OBJS) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean;
	rm -f ${NAME}

re: fclean all

bonus : ${BONUS_FILE}
		
.PHONY: all, clean, fclean, re, bonus

