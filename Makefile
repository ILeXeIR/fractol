NAME = fractol
NAME_BONUS = fractol_bonus

LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_FULL = $(LIBFT_DIR)/$(LIBFT)

MLX_DIR = MLX42

HEADERS	:= -I ./include -I $(MLX_DIR)/include
LIBS	:= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

SOURCES = fractol.c
SOURCES_BONUS = fractol.c

OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

CFLAGS += -Wall -Wextra -Werror -Wunreachable-code -Ofast

all: libmlx $(NAME)

libmlx:
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "Compiling: $(notdir $<)"

$(LIBFT_FULL):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJECTS) $(LIBFT_FULL)
	cc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_FULL) $(LIBS) $(HEADERS)

$(NAME_BONUS): $(OBJECTS_BONUS) $(LIBFT_FULL)
	cc $(CFLAGS) -o $(NAME_BONUS) $(OBJECTS_BONUS) $(LIBFT_FULL) $(LIBS) $(HEADERS)

bonus: libmlx $(NAME_BONUS)

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)
	make clean -C $(LIBFT_DIR)
	rm -rf $(MLX_DIR)/build

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
