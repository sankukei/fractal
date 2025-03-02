# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sankukei <sankukei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:22:30 by leothoma          #+#    #+#              #
#    Updated: 2025/03/01 16:33:49 by sankukei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractal

COMP = cc

SRC =	main.c \
		draw.c \
		utils.c \
		init.c \
		event.c \

OBJS = ${SRC:.c=.o}

%.o: %.c
	$(CC) -g3 -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@


$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean;
	rm -f ${NAME}

re: fclean all

bonus : ${BONUS_FILE}
		
.PHONY: all, clean, fclean, re, bonus

