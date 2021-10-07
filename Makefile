# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsaada <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 13:30:33 by dsaada            #+#    #+#              #
#    Updated: 2021/10/07 17:48:18 by dsaada           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CC = gcc

DEBUG = -g3 -fsanitize=address

CFLAGS = -Wall -Wextra

SRC = ./src/main.c\
	  ./src/time.c\
	  ./src/forks.c\
	  ./src/init.c\
	  ./src/parser.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(DEBUG) -lpthread -o $(NAME)

all: $(NAME)

clean:
	rm -f ./src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all $(NAME) clean fclean re
