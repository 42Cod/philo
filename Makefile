# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 15:42:18 by nmichael          #+#    #+#              #
#    Updated: 2022/09/08 12:19:14 by nmichael         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philo

SRC = ./philo.c ./routine.c ./utils.c ./init.c ./cleaner.c

CC = cc -Wall -Werror -Wextra   -g -fsanitize=address

OBJ = $(SRC:c=o)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f ./*.o

fclean: clean
	rm -f $(NAME)

re: clean fclean $(NAME) $(OBJ)

all: re
