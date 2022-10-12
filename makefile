# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bsomers <bsomers@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/22 14:52:38 by bsomers       #+#    #+#                  #
#    Updated: 2022/10/12 13:05:09 by bsomers       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minirt

LIBFT = libft

LIBMLX42 = libmlx42

SRC = main.c \
	src/vector_math/add.c \
	src/vector_math/distract.c \
	src/vector_math/multiply.c \
	src/vector_math/devide.c \
	src/vector_math/dot.c \
	src/vector_math/unit_vector.c \
	src/color/new_color.c \
	src/color/decide_color.c \
	src/color/put_color.c \
	src/sphere/hit_sphere.c \
	src/ray.c \
	src/renderer.c

INCLUDE = -I include -I ./MLX42/include/MLX42

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBMLX42).a $(LIBFT).a
		$(CC) $(CFLAGS) libmlx42.a $(INCLUDE) -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -L. $(OBJ) -o $(NAME) #-lft

%.o: %.c
		$(CC) -c $(INCLUDE) $(CFLAGS) -o $@ $<

$(LIBFT).a:
	@make -C $(LIBFT)
	@cp $(LIBFT)/$(LIBFT).a .

$(LIBMLX42).a:
	@make -C ./MLX42
	@cp ./MLX42/$(LIBMLX42).a .

clean:
		rm -f $(OBJ)
		@make clean -C $(LIBFT)
		@make clean -C ./MLX42


fclean: clean
		rm -f $(NAME)
		rm -f $(LIBFT).a
		rm -f $(LIBMLX42).a
		@make fclean -C $(LIBFT)

re:
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re