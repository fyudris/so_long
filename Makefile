# === EXECUTABLE NAME ===
NAME            := so_long

# === CONFIGURATION ===
CC              := cc
RM              := rm -f
MKDIR           := /bin/mkdir -p

# === DIRECTORIES ===
# Object file directories
OBJ_DIR_MAND    := obj/mandatory
OBJ_DIR_BONUS   := obj/bonus
# Library & Include directories
LIBFT_DIR       := libft
MLX_DIR         := minilibx
INC_DIR         := include
# Source directories for vpath
SRC_DIRS        := srcs srcs/init srcs/parsing srcs/game srcs/rendering srcs/utils

# === LIBRARIES ===
LIBFT           := $(LIBFT_DIR)/libft.a
MLX_LIB         := $(MLX_DIR)/libmlx.a

# === FLAGS ===
CFLAGS          := -Wall -Wextra -Werror -g -MD
CPPFLAGS        := -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)
LDFLAGS         := -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS          := -lft -lmlx -lXext -lX11 -lm -lz
BONUS_FLAG      := -DBONUS_PART=1

# === SOURCE FILES ===
# Use vpath to tell 'make' where to find source files
vpath %.c $(SRC_DIRS)

MANDATORY_SRCS  := main.c image.c image_utils.c time.c \
                   init.c memory.c parse_map.c validate_content.c \
                   validate_path.c hooks.c render.c textures.c

BONUS_SRCS      := main.c image.c image_utils.c time.c \
                   init_bonus.c memory_bonus.c parse_map.c \
                   validate_content_bonus.c validate_path_bonus.c \
                   hooks_bonus.c render_bonus.c textures_bonus.c logic.c \
                   hooks_utils_bonus.c render_utils_bonus.c \
                   textures_utils_bonus.c render_ui_bonus.c

# === OBJECT FILES ===
# Create separate object lists for each target
OBJS_MANDATORY  := $(addprefix $(OBJ_DIR_MAND)/, $(MANDATORY_SRCS:.c=.o))
OBJS_BONUS      := $(addprefix $(OBJ_DIR_BONUS)/, $(BONUS_SRCS:.c=.o))

# Dependency files for header changes
DEPS            := $(OBJS_MANDATORY:.o=.d) $(OBJS_BONUS:.o=.d)

# --- COLORS ---
GREEN           := \033[0;32m
YELLOW          := \033[0;33m
BLUE_BOLD       := \033[1;34m
RESET           := \033[0m

# === MAIN RULES ===
.DEFAULT_GOAL   := all
all: mandatory

-include $(DEPS)

# --- TARGETS ---
mandatory: $(OBJS_MANDATORY) $(LIBFT) $(MLX_LIB)
	@printf "$(BLUE_BOLD)Linking MANDATORY executable:$(RESET) $(NAME)\n"
	@$(CC) $(OBJS_MANDATORY) -o $(NAME) $(LDFLAGS) $(LDLIBS)
	@printf "$(GREEN)✓ Mandatory project '$(NAME)' created successfully!$(RESET)\n"

bonus: $(OBJS_BONUS) $(LIBFT) $(MLX_LIB)
	@printf "$(BLUE_BOLD)Linking BONUS executable:$(RESET) $(NAME)\n"
	@$(CC) $(OBJS_BONUS) -o $(NAME) $(LDFLAGS) $(LDLIBS)
	@printf "$(GREEN)✓ Bonus project '$(NAME)' created successfully!$(RESET)\n"

# --- COMPILATION RULES ---
$(OBJ_DIR_MAND)/%.o: %.c
	@$(MKDIR) -p $(@D)
	@printf "$(YELLOW)Compiling [MANDATORY]:$(RESET) $<\n"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: %.c
	@$(MKDIR) -p $(@D)
	@printf "$(YELLOW)Compiling [BONUS]:$(RESET) $<\n"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(BONUS_FLAG) -c $< -o $@

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
	@$(RM) -rf obj
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@[ -d $(MLX_DIR) ] && $(MAKE) -s -C $(MLX_DIR) clean >/dev/null 2>&1 || true
	@printf "$(YELLOW)✓ Object files cleaned.\n$(RESET)"

fclean: clean
	@printf "$(GREEN)Cleaning libraries, executable, and MiniLibX folder...$(RESET)\n"
	@$(RM) -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(RM) -rf $(MLX_DIR)
	@printf "$(GREEN)✓ Final clean complete.\n$(RESET)"

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

# --- HELPER RULES ---
norm:
	@printf "$(BLUE_BOLD)Checking Norm compliance...$(RESET)\n"
	@norminette $(INC_DIR) srcs libft

.PHONY: all bonus mandatory clean fclean re norm
.SECONDARY:
.DELETE_ON_ERROR:
