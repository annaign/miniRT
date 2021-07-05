# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/01 23:03:48 by pshagwel          #+#    #+#              #
#    Updated: 2020/09/01 23:03:53 by pshagwel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

LIBFT := libft/
MINILIBX := minilibx/

H_DIR := includes/
SRC_DIR := src/
OBJ_DIR := obj/

INCLUDES := -I$(H_DIR) -I$(LIBFT) -I$(MINILIBX)

SRC :=	main.c \
		get_next_line.c \
		errors.c \
		color.c \
		parse.c \
		check.c \
		hooks_1.c \
		hooks_2.c \
		hooks_3.c \
		triangle.c \
		cylinder.c \
		square.c \
		plane.c \
		sphere.c \
		light.c \
		camera.c \
		resolution.c \
		ambient_light.c \
		parse_rt.c \
		vector_1.c \
		vector_2.c \
		save_bmp.c \
		memory_clean.c \
		intersect.c \
		intersect_calc.c

OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC := gcc
FLAGS := -Wall -Wextra -Werror
# FLAGS += -ggdb3
OPENGL := -L/usr/include/../lib -lXext -lX11 -lm -lbsd

.PHONY: all clean fclean makeobjdir re bonus leaks

# create folders
$(shell mkdir -p $(OBJ_DIR))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c ./$(H_DIR)minirt.h
		$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
		@make -C $(LIBFT)
		cd $(MINILIBX) && $(MAKE) all
		$(CC) $(FLAGS) $(OBJ) $(INCLUDES) $(LIBFT)libft.a $(MINILIBX)libmlx_Linux.a \
		$(OPENGL) -o $(NAME)

clean:
		/bin/rm -rf $(OBJ_DIR)
		cd $(LIBFT) && $(MAKE) clean
		cd $(MINILIBX) && $(MAKE) clean

fclean: clean
		/bin/rm -f $(NAME)
		cd $(LIBFT) && $(MAKE) fclean

makeobjdir:
		$(shell mkdir -p $(OBJ_DIR))

bonus: all

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s \
	./miniRT ./scenes/31_test_multy-obj.rt --save

re: fclean makeobjdir all