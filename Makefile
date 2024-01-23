NAME = fractol
NAME_BONUS = fractol_bonus

LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_FULL = $(LIBFT_DIR)/$(LIBFT)

LIBMLX = libmlx42.a
MLX_DIR = MLX42
MLX_FULL = $(MLX_DIR)/build/$(LIBMLX)

HEADERS	:= -I $(MLX_DIR)/include
LIBS	:= $(LIBFT_FULL) $(MLX_FULL) -ldl -lglfw -pthread -lm

SOURCES = fractol.c helpers.c hooks.c colors.c
SOURCES_BONUS = fractol.c helpers.c hooks.c colors.c

OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

CFLAGS += -Wall -Wextra -Werror -Wunreachable-code -Ofast

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ $(HEADERS)

$(LIBFT_FULL):
	make -C $(LIBFT_DIR)

$(MLX_FULL):
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(NAME): $(OBJECTS) $(LIBFT_FULL) $(MLX_FULL)
	cc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS) $(HEADERS)

$(NAME_BONUS): $(OBJECTS_BONUS) $(LIBFT_FULL) $(MLX_FULL)
	cc $(CFLAGS) -o $(NAME_BONUS) $(OBJECTS_BONUS) $(LIBS) $(HEADERS)

bonus: $(NAME_BONUS)

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make fclean -C $(LIBFT_DIR)
	rm -rf $(MLX_DIR)/build

re: fclean all

.PHONY: all clean fclean re bonus
