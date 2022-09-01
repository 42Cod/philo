# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 15:42:18 by nmichael          #+#    #+#              #
#    Updated: 2022/09/01 14:11:07 by nmichael         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philo

SRC = ./philo.c ./routine.c ./utils.c ./init.c ./cleaner.c

CC = cc -Wall -Werror -Wextra #-fsanitize=address

OBJ = $(SRC:c=o)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f ./src/*.o

fclean: clean
	rm -f $(NAME)

re: clean fclean $(NAME)

all: re
