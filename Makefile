# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 08:10:39 by yogun             #+#    #+#              #
#    Updated: 2023/01/15 11:17:52 by yogun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFTDIR = ./libft

MLXDIR = ./mlx

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

SRC =	cube3d.c \
		game/ft_map_process.c \
		game/ft_map_control.c \
		game/ft_map_translate.c \
		game/ft_game_render.c \
		game/ft_game_start.c \
		game/math_functions.c \
		game/minimap.c \
		game/ft_keys.c \
		game/ft_horizontal_ray.c \
		game/ft_vertical_ray.c \
		game/map_update.c \
		game/line_draw.c \
		game/keys_rotate.c \
		game/sprite.c \
		game/utils.c \
		game/ft_initdata.c \
		game/ft_check_map_format.c \
		game/ft_free.c \
		game/ft_error.c \
		game/ft_exit_game.c \
		game/ft_start.c \

INCLIBFT = -L./libft -lft
INCMLX = -L./mlx -lmlx

OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	@make -C $(LIBFTDIR)
	@make -C $(MLXDIR)
	${CC} ${OBJ} ${INCLIBFT} ${INCMLX} -framework OpenGL -framework AppKit -o ${NAME}

all: ${NAME}

bonus: all

clean:
	${RM} ${OBJ} ${DEP}
	@cd $(LIBFTDIR) && $(MAKE) fclean
	@cd $(MLXDIR) && $(MAKE) clean

fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEP)