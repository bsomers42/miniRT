# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bsomers <bsomers@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/22 14:52:38 by bsomers       #+#    #+#                  #
#    Updated: 2022/09/22 16:30:41 by jaberkro      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minirt

LIBFT = libft

LIBMLX42 = libmlx42

SRC = main.c

INCLUDE = -I include -I ./MLX42/include/MLX42

CFLAGS = -Wall -Wextra -Werror -g

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