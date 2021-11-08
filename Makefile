# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsaada <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 13:30:33 by dsaada            #+#    #+#              #
#    Updated: 2021/11/08 13:07:24 by dsaada           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CC = gcc

DEBUG = -g3 -fsanitize=thread

CFLAGS = -Wall -Wextra

SRC = ./src/main.c\
	  ./src/time.c\
	  ./src/forks.c\
	  ./src/init.c\
	  ./src/parser.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) ./src/philosophers.h
	$(CC) $(OBJ) -lpthread -o $(NAME)

all: $(NAME)

clean:
	rm -f ./src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all $(NAME) clean fclean re
