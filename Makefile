# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 19:54:35 by yogun             #+#    #+#              #
#    Updated: 2022/12/12 14:56:12 by yogun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFTDIR = ./libft

MLXDIR = ./mlx

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

SRC =	cub3d.c \
		error_print.c \
		is_map_format_ok.c \
		parse_map.c \
		parse_map_utils.c \
		

OBJ = ${SRC:.c=.o}

INCLIBFT = -L./libft -lft
INMLX = -L./mlx -lmlx

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	@make -C $(LIBFTDIR)
	@make -C $(MLXDIR)
	${CC} ${OBJ} ${INCLIBFT} ${INMLX} -framework OpenGL -framework AppKit -o ${NAME}

all: ${NAME}

bonus: all

clean:
	${RM} ${OBJ}
	@cd $(LIBFTDIR) && $(MAKE) fclean
	@cd $(MLXDIR) && $(MAKE) clean

fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re bonus
