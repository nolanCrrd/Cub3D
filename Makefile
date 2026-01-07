CC=cc
NAME = Cub3d
SRC_DIR = src/

SRCS = $(SRC_DIR)cub3d.c \

OBJ_DIR = .build/
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
LIBFT = ./libft/libft.a

FSANITIZE = -fsanitize=address,undefined,leak -fno-omit-frame-pointer \
            -fsanitize-recover=address

CFLAGS = -Wall -Werror -Wextra -g \
		-I include \
		-I libft \
		-I libft/ft_printf/includes \
		-I libft/get_next_line/

LDFLAGS = $(LIBFT) -lreadline

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

$(NAME): $(OBJS) $(LIBFT)
	@echo ""
	@echo "================================"
	@echo "Creating minishell..."
	@echo "================================"
	@echo ""
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT):
	@echo ""
	@echo "================================"
	@echo "Compiling libft objects..."
	@echo "================================"
	@echo ""
	$(MAKE) -C libft

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) -C libft fclean

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

re: fclean all

.PHONY: all fclean clean re
