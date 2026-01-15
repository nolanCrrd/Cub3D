CC=cc
NAME = cub3D
NAME_BONUS = cub3D_bonus
SRC_DIR = src/
MLX_DIR = mlx/

SRCS_PARSING = $(SRC_DIR)parsing/check_file.c \
	$(SRC_DIR)parsing/parser.c \
	$(SRC_DIR)parsing/init_textures.c \
	$(SRC_DIR)parsing/init_textures_verif.c \
	$(SRC_DIR)parsing/init_map.c \
	$(SRC_DIR)parsing/init_player.c \
	$(SRC_DIR)parsing/map_checker.c

SRCS_PARSING_BONUS = $(SRC_DIR)parsing/check_file_bonus.c \
	$(SRC_DIR)parsing/parser.c \
	$(SRC_DIR)parsing/init_textures_bonus.c \
	$(SRC_DIR)parsing/init_textures_utils_bonus.c \
	$(SRC_DIR)parsing/init_textures_verif.c \
	$(SRC_DIR)parsing/init_map.c \
	$(SRC_DIR)parsing/init_player.c \
	$(SRC_DIR)parsing/map_checker_bonus.c

SRCS_MOVEMENT = $(SRC_DIR)movement_logic/movement.c \
	$(SRC_DIR)movement_logic/rotate.c \

SRCS_MOVEMENT_BONUS = $(SRC_DIR)movement_logic/movement.c \
	$(SRC_DIR)movement_logic/rotate.c \
	$(SRC_DIR)movement_logic/mouse_bonus.c

SRCS_RENDER = $(SRC_DIR)render/renderer.c \
	$(SRC_DIR)render/hooks/window_hooks.c \
	$(SRC_DIR)render/hooks/keydown_hooks.c \
	$(SRC_DIR)render/hooks/keyup_hooks.c \
	$(SRC_DIR)render/update.c \
	$(SRC_DIR)render/raycaster/raycaster.c \
	$(SRC_DIR)render/raycaster/wall_casting.c \

SRCS_RENDER_BONUS = $(SRC_DIR)render/renderer_bonus.c \
	$(SRC_DIR)render/hooks/window_hooks.c \
	$(SRC_DIR)render/hooks/keydown_hooks.c \
	$(SRC_DIR)render/hooks/keyup_hooks.c \
	$(SRC_DIR)render/update_bonus.c \
	$(SRC_DIR)render/raycaster/raycaster_bonus.c \
	$(SRC_DIR)render/raycaster/wall_casting_bonus.c \
	$(SRC_DIR)render/raycaster/floor_casting_bonus.c

SRCS_UTILS = $(SRC_DIR)utils/is_blank.c \
	$(SRC_DIR)utils/remove_spaces.c \
	$(SRC_DIR)utils/skip_empty_lines.c \
	$(SRC_DIR)utils/refresh_frame_time.c \
	$(SRC_DIR)utils/get_distance.c \
	$(SRC_DIR)utils/draw_square.c \
	$(SRC_DIR)utils/get_near_elmt.c \
	$(SRC_DIR)utils/get_tile.c

SRCS_HUD_BONUS = $(SRC_DIR)render/hud/map_bonus.c \
	$(SRC_DIR)render/hud/rec_bonus.c

SRCS = $(SRC_DIR)cub3d.c \
	$(SRC_DIR)ctx.c \
	$(SRCS_UTILS) \
	$(SRCS_PARSING) \
	$(SRCS_MOVEMENT) \
	$(SRCS_RENDER)

SRCS_BONUS = $(SRC_DIR)cub3d.c \
	$(SRC_DIR)ctx.c \
	$(SRCS_UTILS) \
	$(SRCS_PARSING_BONUS) \
	$(SRCS_MOVEMENT_BONUS) \
	$(SRCS_RENDER_BONUS) \
	$(SRCS_HUD_BONUS)

OBJ_DIR = .build/
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJS_BONUS = $(SRCS_BONUS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
LIBFT = ./libft/libft.a

FSANITIZE = -fsanitize=address,undefined,leak -fno-omit-frame-pointer \
            -fsanitize-recover=address

CFLAGS = -Wall -Werror -Wextra -g \
		-I include \
		-I libft \
		-I libft/ft_printf/includes \
		-I libft/get_next_line/ \
		-I $(MLX_DIR)includes \
		-Ofast

LDFLAGS = $(LIBFT) -lm $(MLX_DIR)libmlx.so -lSDL2

ifdef SANITIZE
	CFLAGS += $(FSANITIZE)
	LDFLAGS += $(FSANITIZE)
endif

all: $(NAME)

bonus: $(NAME_BONUS)

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
	@echo "Creating cub3D..."
	@echo "================================"
	@echo ""
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX_DIR)libmlx.so
	@echo ""
	@echo "================================"
	@echo "Creating cub3D_bonus..."
	@echo "================================"
	@echo ""
	$(CC) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME_BONUS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)utils
	@mkdir -p $(OBJ_DIR)parsing
	@mkdir -p $(OBJ_DIR)render
	@mkdir -p $(OBJ_DIR)movement_logic
	@mkdir -p $(OBJ_DIR)render/hooks
	@mkdir -p $(OBJ_DIR)render/raycaster
	@mkdir -p $(OBJ_DIR)render/hud/map_bonus.c
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
