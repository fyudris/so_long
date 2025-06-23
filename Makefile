# === CONFIGURATION ===
NAME            := so_long
CC              := cc
RM              := rm -f

# === DIRECTORIES ===
OBJ_DIR         := obj
SRC_DIR         := srcs
INC_DIR         := include
LIBFT_DIR       := libft
MLX_DIR         := minilibx

# === LIBRARIES ===
LIBFT           := $(LIBFT_DIR)/libft.a
MLX_LIB         := $(MLX_DIR)/libmlx.a

# === FLAGS (Improved Separation) ===
CFLAGS          := -Wall -Wextra -Werror -g -MD
# Include paths for the compiler
CPPFLAGS        := -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)
# Library search paths for the linker
LDFLAGS         := -L$(LIBFT_DIR) -L$(MLX_DIR)
# Libraries to link
LDLIBS          := -lft -lmlx -lXext -lX11 -lm -lz

# === SOURCE FILES (Your excellent vpath method) ===
vpath %.c $(SRC_DIR) $(SRC_DIR)/init $(SRC_DIR)/game $(SRC_DIR)/parsing $(SRC_DIR)/rendering
SRCS            := main.c init.c memory.c hooks.c logic.c parse_map.c \
                   validate_content.c validate_path.c render.c image.c textures.c

# === OBJECTS & DEPENDENCIES ===
OBJS            := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS            := $(OBJS:.o=.d)

# --- COLORS ---
GREEN           := \033[0;32m
YELLOW          := \033[0;33m
BLUE_BOLD       := \033[1;34m
RESET           := \033[0m

# === RULES ===
.DEFAULT_GOAL   := all

-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@printf "$(BLUE_BOLD)Linking executable:$(RESET) $@\n"
	@$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)
	@printf "$(GREEN)✓ Project '$@' created successfully!$(RESET)\n"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@/bin/mkdir -p $(@D)
	@printf "$(YELLOW)Compiling:$(RESET) $<\n"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)

# --- LIBRARY RULES ---
$(LIBFT):
	@printf "$(BLUE_BOLD)Building libft...$(RESET)\n"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX_LIB): $(MLX_DIR)
	@printf "$(BLUE_BOLD)Building MiniLibX...$(RESET)\n"
	@if ! pkg-config --exists x11 xext; then \
		echo "Error: X11 development libraries not found."; \
		echo "On Ubuntu, install with: sudo apt-get install libx11-dev libxext-dev"; \
		exit 1; \
	fi
	@$(MAKE) -s -C $(MLX_DIR)
	@printf "$(GREEN)✓ MiniLibX built successfully$(RESET)\n"

$(MLX_DIR):
	@printf "$(BLUE_BOLD)Cloning MiniLibX from git...$(RESET)\n"
	@git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

# --- CLEAN RULES ---
clean:
	@printf "$(YELLOW)Cleaning project object files...$(RESET)\n"
	@$(RM) -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	# Silently clean MiniLibX object files, but leave the source folder
	@[ -d $(MLX_DIR) ] && $(MAKE) -s -C $(MLX_DIR) clean >/dev/null 2>&1 || true
	@printf "$(YELLOW)✓ Object files cleaned.\n$(RESET)"

fclean: clean
	@printf "$(GREEN)Cleaning libraries and executable...$(RESET)\n"
	@$(RM) -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@printf "$(GREEN)✓ Final clean complete.\n$(RESET)"

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re
.SECONDARY:
.DELETE_ON_ERROR:
