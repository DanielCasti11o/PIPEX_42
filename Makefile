# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 10:53:25 by dacastil          #+#    #+#              #
#    Updated: 2025/03/18 13:28:04 by dacastil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = pipex
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g3
SRC_DIR = ./src
INCLUDE_DIR = ./pipex.h
SRC = $(wildcard $(SRC_DIR)/pipex.c)
INCLUDE = $(wildcard $(INCLUDE_DIR)/pipex.h)
OBJS = $(SRC:.c=.o)

all: $(EXEC)

	$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(FLAGS)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(OBJS) $(EXEC)

re: fclean $(EXEC)

.PHONY: all clean fclean re
