CC=cc
NAME = cub3D
SRC_DIR = src/
MLX_DIR = mlx/

SRCS_PARSING = $(SRC_DIR)parsing/check_file.c \
	$(SRC_DIR)parsing/parser.c \
	$(SRC_DIR)parsing/init_textures.c \
	$(SRC_DIR)parsing/init_map.c \
	$(SRC_DIR)parsing/init_player.c \
	$(SRC_DIR)parsing/map_checker.c

SRCS_RENDER = $(SRC_DIR)render/renderer.c \

SRCS_UTILS = $(SRC_DIR)utils/is_blank.c \
	$(SRC_DIR)utils/remove_spaces.c \
	$(SRC_DIR)utils/skip_empty_lines.c

SRCS = $(SRC_DIR)cub3d.c \
	$(SRC_DIR)ctx.c \
	$(SRCS_UTILS) \
	$(SRCS_PARSING) \
	$(SRCS_RENDER)

OBJ_DIR = .build/
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
LIBFT = ./libft/libft.a

FSANITIZE = -fsanitize=address,undefined,leak -fno-omit-frame-pointer \
            -fsanitize-recover=address

CFLAGS = -Wall -Werror -Wextra -g \
		-I include \
		-I libft \
		-I libft/ft_printf/includes \
		-I libft/get_next_line/ \
		-I $(MLX_DIR)includes

LDFLAGS = $(LIBFT) -lreadline -lm $(MLX_DIR)libmlx.so -lSDL2

ifdef SANITIZE
	CFLAGS += $(FSANITIZE)
	LDFLAGS += $(FSANITIZE)
endif

all: $(NAME)

sanitize:
	@echo ""
	@echo "================================"
	@echo "Recompiling with fsanitize flags..."
	@echo "================================"
	@echo ""
	$(MAKE) re SANITIZE=1
	@$(MAKE) run_sanitize
run_sanitize:
	@echo ""
	@echo "================================"
	@echo "Running with AddressSanitizer..."
	@echo "================================"
	@echo ""
	@ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 LSAN_OPTIONS=report_objects=1 ./$(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_DIR)libmlx.so
	@echo ""
	@echo "================================"
	@echo "Creating minishell..."
	@echo "================================"
	@echo ""
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)utils
	@mkdir -p $(OBJ_DIR)parsing
	@mkdir -p $(OBJ_DIR)render
	$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT):
	@echo ""
	@echo "================================"
	@echo "Compiling libft objects..."
	@echo "================================"
	@echo ""
	$(MAKE) -C libft

$(MLX_DIR)libmlx.so:
	$(MAKE) -C mlx -j

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) -C libft fclean

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

re: fclean all

.PHONY: all fclean clean re
