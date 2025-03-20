# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 10:53:25 by dacastil          #+#    #+#              #
#    Updated: 2025/03/20 15:44:21 by dacastil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = pipex
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g3 -I ./libft_bonus -I ./include
SRC_DIR = ./src
INCLUDE_DIR = ./pipex.h
LIBFT_DIR = ./libft_bonus
LIBFT = $(LIBFT_DIR)/libft.a
SRC =$(SRC_DIR)/pipex.c $(SRC_DIR)/process.c $(SRC_DIR)/utils.c
OBJS = $(SRC:.c=.o)

all: $(LIBFT) $(EXEC)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(EXEC): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(EXEC) $(FLAGS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	$(RM) $(OBJS) $(EXEC)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
