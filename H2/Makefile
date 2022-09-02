# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hngo <hngo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/01 17:31:05 by hngo              #+#    #+#              #
#    Updated: 2022/03/10 19:02:59 by hngo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = ./src/philo.c ./src/init.c ./src/utils.c ./src/time.c ./src/routine.c ./src/eat.c

CC = cc -Wall -Werror -Wextra

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
