# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 08:10:39 by yogun             #+#    #+#              #
#    Updated: 2023/01/28 18:16:34 by bderya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFTDIR = ./src/libft

MLXDIR = ./mlx

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

# COLORS
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[36m"
X = "\033[0m"
########


# SOURCE FILES
SRC =	cube3d.c \
		src/ft_map_process.c \
		src/ft_map_control.c \
		src/ft_map_translate.c \
		src/ft_game_render.c \
		src/ft_game_start.c \
		src/math_functions.c \
		src/minimap.c \
		src/ft_keys.c \
		src/ft_horizontal_ray.c \
		src/ft_vertical_ray.c \
		src/map_update.c \
		src/line_draw.c \
		src/keys_rotate.c \
		src/sprite.c \
		src/utils.c \
		src/ft_initdata.c \
		src/ft_check_map_format.c \
		src/ft_free.c \
		src/ft_error.c \
		src/ft_exit_game.c \
		src/ft_start.c \
################################

INCLIBFT = ./src/libft/libft.a 
INCMLX = -L./mlx -lmlx
LINK_FLAGS += -Lmlx -lmlx -framework OpenGL -framework AppKit
OBJ = ${SRC:.c=.o}

all: ${NAME}

LSANLIB = /LeakSanitizer/liblsan.a
lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK_FLAGS += -LLeakSanitizer -llsan -lc++
lsan: fclean $(LSANLIB)
lsan: all

$(LSANLIB): 
	@if [ ! -d "LeakSanitizer" ]; then git clone git@github.com:bderya/LeakSanitizer.git; fi
	$(MAKE) -C LeakSanitizer


${NAME}: ${OBJ}
	make -C $(LIBFTDIR)
	make -C $(MLXDIR) CFLAGS+="-Wno-deprecated -DSTRINGPUTX11 -O2"
	${CC} ${OBJ} $(LINK_FLAGS) ${INCLIBFT} ${INCMLX} -framework OpenGL -framework AppKit -o ${NAME}
	@echo $(B)
	@echo "                       _|         _|_|_|     _|_|_|  "
	@echo "   _|_|_|   _|    _|   _|_|_|           _|   _|    _|"
	@echo " _|         _|    _|   _|    _|     _|_|     _|    _|"
	@echo " _|         _|    _|   _|    _|         _|   _|    _|"
	@echo "   _|_|_|     _|_|_|   _|_|_|     _|_|_|     _|_|_|  "
	@echo $(X)

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
