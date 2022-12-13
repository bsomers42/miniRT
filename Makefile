# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bsomers <bsomers@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/22 14:52:38 by bsomers       #+#    #+#                  #
#    Updated: 2022/12/13 16:09:30 by bsomers       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

FLAGS = -Wall -Wextra -Werror -O3
INCLUDE = -I include -I ./MLX42/include/MLX42 -I ./libft

LIBFT_DIR = libft/
LIBFT = libft/libft.a
LIBMLX42 = libmlx42.a

SRC_DIR = src
BUILD_DIR = obj

SRC = main.c \
	init.c \
	threads.c \
	error.c \
	utils.c \
	parser/parse.c \
	parser/list_add.c \
	parser/stod_atoi_map_elems.c \
	parser/get_next_line.c \
	parser/get_map.c \
	parser/parsing_checks.c \
	parser/malloc_checks.c \
	tracer/antialias_color.c \
	tracer/point_ray_get_color.c \
	tracer/point_ray_utils.c \
	tracer/put_color.c \
	color/new_color.c \
	color/color_math_basics.c \
	color/color_math_advanced.c \
	point/new_point.c \
	point/point_math_basics.c \
	point/point_math_advanced.c \
	hit/hit_cone.c \
	hit/hit_cone_cap.c \
	hit/hit_sphere.c \
	hit/hit_anything.c \
	hit/hit_plane.c \
	hit/hit_cylinder_tube.c \
	hit/hit_cylinder_cap.c \
	hit/hit_utils.c

OBJ := $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
SRC := $(addprefix $(SRC_DIR)/, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(LIBMLX42)
	$(CC) $^ $(FLAGS) $(INCLUDE) -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -L. -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c $(INCLUDE) $(FLAGS) -o $@ $<

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@cp ./$(LIBFT) .

$(LIBMLX42):
	@make -C ./MLX42
	@cp ./MLX42/$(LIBMLX42) .

clean:
	rm -rf $(BUILD_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C ./MLX42

fclean: clean
	rm -f $(NAME)
	rm -f libft.a
	rm -f $(LIBMLX42)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
