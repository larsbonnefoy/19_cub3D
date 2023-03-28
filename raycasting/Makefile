###################################################################################################
##############################################PROGRAM##############################################
###################################################################################################
.SILENT:
###__MAIN PROGRAM__###

NAME = raycaster

FILES =  raycaster.c 

SRCS = raycaster.c raycasting_visualizer.c

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Os -O2 -O3

FFLAGS = -fsanitize=address -g

CC = @cc

RM = @rm -f

###__OS DETECTION__### no windows support for the moment

DETECTED_OS = $(shell uname)

###__LIBFT__##

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

###__GNL__##
GNL_DIR = get_next_line

GNL = $(GNL_DIR)/gnl.a

###__MLX__###

ifeq ($(DETECTED_OS), Linux)

MLX_DIR = mlx_linux 

MLX_PATH = $(MLXDIR)/libmlx_linux.a

MLX = -Lmlx_linux -lmlx_Linux -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz 

else

MLX_DIR = mlx 

MLX_PATH = $(MLXDIR)/libmlx.a

MLX = -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit

endif
#etgst
###__COMPILATION__###
$(NAME): $(OBJ)
		$(PRINT_OS)
#		# $(PRINT) "$(RED)making:	$(NOCOLOR)$(LIBFT_DIR)"
#		# @make --no-print-directory -C $(LIBFT_DIR)
#		# $(PRINT) "$(GREEN)done:\t$(NOCOLOR)$(LIBFT_DIR)"
#		# $(PRINT) "$(RED)making:\t$(NOCOLOR)$(GNL_DIR)"
#		# @make --no-print-directory -C $(GNL_DIR)
#		# $(PRINT) "$(GREEN)done:\t$(NOCOLOR)$(GNL_DIR)"
		$(PRINT) "$(RED)making:\t$(NOCOLOR)$(MLX_DIR)"
		@make --no-print-directory -C $(MLX_DIR)
		$(PRINT) "$(GREEN)done:\t$(NOCOLOR)$(MLX_DIR)"
		$(PRINT) "$(CYAN)making:\t$(NOCOLOR)$(NAME)"
		$(CC) $(CFLAGS) $(FFLAGS) -g $(OBJ) $(MLX) -o $(NAME)
		$(PRINT) "$(GREEN)done:\t$(NOCOLOR)$(NAME)"

.c.o:
		$(CC) $(CLFAGS) $(FFLAGS) -g -c $< -o $(<:.c=.o)

###__RULES__###
all: $(NAME)

clean:
#		@make --no-print-directory clean -C $(LIBFT_DIR)
#		@make --no-print-directory clean -C $(GNL_DIR)
		$(RM) $(OBJ)

fclean: clean
#		@make --no-print-directory fclean -C $(LIBFT_DIR)
#		# @make --no-print-directory fclean -C $(GNL_DIR)
		@make --no-print-directory clean -C $(MLX_DIR)
		$(RM) $(NAME)

re :	fclean $(NAME)

.PHONY: all clean fclean re

###################################################################################################
############################################MISC###################################################
###################################################################################################

###__PRINT__###

PRINT = echo -e

# endif
PRINT_OS = echo -e "$(CYAN)OS:\t$(NOCOLOR)$(DETECTED_OS)"

###__COLORS__###
NOCOLOR = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
