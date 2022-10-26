# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bsomers <bsomers@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/22 14:52:38 by bsomers       #+#    #+#                  #
#    Updated: 2022/10/26 11:17:18 by jaberkro      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minirt

FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
INCLUDE = -I include -I ./MLX42/include/MLX42 -I ./libft

LIBFT_DIR = libft/
LIBFT = libft/libft.a
LIBMLX42 = libmlx42.a

SRC_DIR = src
BUILD_DIR = obj

SRC = main.c \
	init.c \
	error.c \
	utils.c \
	parser/parse.c \
	parser/parse_utils.c \
	parser/list_add.c \
	vector_math/add.c \
	vector_math/substract.c \
	vector_math/multiply.c \
	vector_math/divide.c \
	vector_math/dot.c \
	vector_math/unit_vector.c \
	vector_math/clamp.c \
	color/new_color.c \
	color/antialias_color.c \
	color/point_ray_get_color.c \
	color/calculate_ambient_color.c \
	color/put_color.c \
	coord/new_coord.c \
	hit/hit_sphere.c \
	hit/hit_anything.c \
	threads.c

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
