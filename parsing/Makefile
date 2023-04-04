# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 13:10:56 by lbonnefo          #+#    #+#              #
#    Updated: 2023/04/04 14:41:09 by lbonnefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D 

FILES = parsing.c pathfinding.c pathfinding_mvt.c error.c check_id.c check_map.c \

SRCS = $(FILES)

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

###LIB INCLUDES###

LIBFT_DIR = ../libft

LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = ../gnl

GNL = $(GNL_DIR)/gnl.a

$(NAME): $(OBJ)
		@make -C $(LIBFT_DIR)
		@make -C $(GNL_DIR)
		@cc $(CFLAGS) -g $(OBJ) $(LIBFT) $(GNL) -o $(NAME)
.c.o:
		@cc $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

clean:
		@make --no-print-directory clean -C $(LIBFT_DIR)
		@make --no-print-directory clean -C $(GNL_DIR)
		rm -f $(OBJ) 

fclean: clean
		@make --no-print-directory fclean -C $(LIBFT_DIR)
		@make --no-print-directory fclean -C $(GNL_DIR)
		rm -f $(NAME)

re :	fclean $(NAME)
	
.PHONY: all clean fclean re 

