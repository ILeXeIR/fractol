NAME = fractol

LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_FULL = $(LIBFT_DIR)/$(LIBFT)

LIBMLX = libmlx42.a
MLX_DIR = MLX42
MLX_FULL = $(MLX_DIR)/build/$(LIBMLX)

HEADERS	:= -I $(MLX_DIR)/include
LIBS	:= $(LIBFT_FULL) $(MLX_FULL) -ldl -lglfw -pthread -lm

SOURCES = fractol.c helpers.c hooks.c colors.c calculators.c utils.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS += -Wall -Wextra -Werror -Ofast

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ $(HEADERS)

$(LIBFT_FULL):
	make -C $(LIBFT_DIR)

$(MLX_FULL):
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(NAME): $(OBJECTS) $(LIBFT_FULL) $(MLX_FULL)
	cc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS) $(HEADERS)

bonus: $(NAME)

clean:
	rm -f $(OBJECTS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	rm -rf $(MLX_DIR)/build

re: fclean all

.PHONY: all clean fclean re bonus
