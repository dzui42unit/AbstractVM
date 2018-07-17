# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzui <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 15:02:50 by dzui              #+#    #+#              #
#    Updated: 2018/07/17 20:40:44 by dzui             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

SRC =  main.cpp OperandFactory.cpp VM.cpp VM_Instructions.cpp VM_Parser.cpp Lexer.cpp

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++14

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
