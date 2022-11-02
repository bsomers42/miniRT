# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bsomers <bsomers@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/22 14:52:38 by bsomers       #+#    #+#                  #
#    Updated: 2022/10/21 14:41:19 by bsomers       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minirt

FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
INCLUDE = -I include -I ./MLX42/include/MLX42 -I ./libft

LIBFT_DIR = libft/
LIBFT = libft/libft.a
LIBMLX42 = libmlx42.a

SRC_DIR = src
BUILD_DIR = obj

SRC = main.c \
	error.c \
	utils.c \
	parser/parse.c \
	parser/list_add.c \
	parser/get_next_line.c \
	parser/get_map.c \
	vector_math/add.c \
	vector_math/distract.c \
	vector_math/multiply.c \
	vector_math/devide.c \
	vector_math/dot.c \
	vector_math/unit_vector.c \
	color/new_color.c \
	color/decide_color.c \
	color/put_color.c \
	color/antialias_color.c \
	sphere/hit_sphere.c \
	threads.c

OBJ := $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
SRC := $(addprefix $(SRC_DIR)/, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(LIBMLX42)
	$(CC) $(OBJ) $(FLAGS) $(INCLUDE) $(LIBMLX42) $(LIBFT) -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -L. -o $(NAME)

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
