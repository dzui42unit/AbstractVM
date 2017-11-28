# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzui <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 15:02:50 by dzui              #+#    #+#              #
#    Updated: 2017/11/28 18:43:37 by dzui             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

SRC =  main.cpp OperandFactory.cpp

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++11

$(NAME): $(OBJ)
		clang++ $(FLAGS) $(OBJ) -o $(NAME)

%.o:%.cpp
		clang++ $(FLAGS) -c -o $@ $<

all: $(NAME)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME) $(OBJ)

re:	fclean $(NAME)
