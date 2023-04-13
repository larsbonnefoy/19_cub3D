# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 13:10:56 by lbonnefo          #+#    #+#              #
#    Updated: 2023/04/13 08:38:43 by hdelmas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D 

FILES_PARSING = parsing.c error.c check_id.c check_id_utils.c map_validation.c map_validation_utils.c\

FILES_RAYCASTING = raycasting_visualizer.c next_edge.c in_wall.c ray_len.c rays_gen.c turn.c frame.c move.c key_management.c texture.c\

SRCS = $(addprefix parsing/, $(FILES_PARSING)) $(addprefix raycasting/, $(FILES_RAYCASTING))

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Os -O2 -O3

FFLAGS = -fsanitize=address -g

###LIB INCLUDES###

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = gnl

GNL = $(GNL_DIR)/gnl.a

MLX_DIR = mlx 

MLX_PATH = $(MLXDIR)/libmlx.a

MLX = -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit

$(NAME): $(OBJ)
		@make -C $(LIBFT_DIR)
		@make -C $(GNL_DIR)
		@make -C $(MLX_DIR)
		@cc $(CFLAGS) $(FFLAGS) -g $(OBJ) $(LIBFT) $(GNL) $(MLX) -o $(NAME)
.c.o:
		@cc $(CFLAGS) $(FFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

clean:
		@make --no-print-directory clean -C $(LIBFT_DIR)
		@make --no-print-directory clean -C $(GNL_DIR)
		rm -f $(OBJ) 

fclean: clean
		@make --no-print-directory fclean -C $(LIBFT_DIR)
		@make --no-print-directory fclean -C $(GNL_DIR)
		@make --no-print-directory clean -C $(MLX_DIR)
		rm -f $(NAME)

re :	fclean $(NAME)
	
.PHONY: all clean fclean re 

