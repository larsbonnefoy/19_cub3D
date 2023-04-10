# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 08:30:21 by lbonnefo          #+#    #+#              #
#    Updated: 2023/04/06 15:45:29 by lbonnefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

SRCS =	get_next_line.c \
		get_next_line_utils.c \

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

$(NAME): $(OBJ)
		@ar -rc $(NAME) $(OBJ)

.c.o:
		@cc $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

clean:
		rm -f $(OBJ) 

fclean: clean
		rm -f $(NAME)

re :	fclean $(NAME)
	
.PHONY: all clean fclean re 
