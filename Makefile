# === EXECUTABLE NAME ===
NAME            := so_long

# === CONFIGURATION ===
CC              := cc
RM              := rm -f
MKDIR           := /bin/mkdir -p
SILENT          := @

# === OS DETECTION ===
OS              := $(shell uname -s)

# === DIRECTORIES ===
OBJ_DIR         := obj
LIBFT_DIR       := libft
MLX_DIR         := minilibx
INC_DIR         := include
SRC_DIRS        := srcs srcs/init srcs/parsing srcs/game srcs/rendering srcs/utils

# === LIBRARIES ===
LIBFT           := $(LIBFT_DIR)/libft.a
MLX_LIB         := $(MLX_DIR)/libmlx.a

# === FLAGS & OS-SPECIFIC SETTINGS ===
CFLAGS          := -Wall -Wextra -Werror -g -MD
CPPFLAGS        := -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)
LDFLAGS         := -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS          := -lft -lmlx -lXext -lX11 -lm

ifeq ($(OS), Linux)
    MLX_GIT_REPO := https://github.com/42Paris/minilibx-linux.git
else ifeq ($(OS), Darwin)
    MLX_GIT_REPO := https://github.com/42Paris/minilibx-linux.git
    LDFLAGS      += -L/opt/X11/lib
endif

# === CONDITIONAL SOURCE FILES (THE FIX) ===
# By default, use mandatory sources
SRCS_LIST       := main.c image.c image_utils.c time.c \
                   init.c memory.c parse_map.c validate_content.c \
                   validate_path.c hooks.c render.c textures.c
# If BONUS=1 is passed to make, override with bonus sources
ifeq ($(BONUS), 1)
    CFLAGS      += -DBONUS_PART=1
    SRCS_LIST   := main.c image.c image_utils.c time.c \
                   init_bonus.c memory_bonus.c parse_map.c \
                   validate_content_bonus.c validate_path_bonus.c \
                   hooks_bonus.c render_bonus.c textures_bonus.c logic.c \
                   hooks_utils_bonus.c render_utils_bonus.c \
                   textures_utils_bonus.c render_ui_bonus.c
endif

vpath %.c $(SRC_DIRS)
OBJS            := $(addprefix $(OBJ_DIR)/, $(SRCS_LIST:.c=.o))
DEPS            := $(OBJS:.o=.d)

# === COLORS ===
GREEN           := \033[0;32m
YELLOW          := \033[0;33m
BLUE_BOLD       := \033[1;34m
CYAN            := \033[0;36m
RESET           := \033[0m

# === MAIN RULES ===
.DEFAULT_GOAL   := all
all: $(NAME)

bonus:
	$(MAKE) BONUS=1 all

-include $(DEPS)

# --- SINGLE UNIFIED TARGET ---
$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(SILENT)printf "\n"
	$(SILENT)printf "$(BLUE_BOLD)Linking -> $(RESET)$(NAME)\n"
	$(SILENT)$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(LDLIBS)
	$(SILENT)printf "$(GREEN)✓ Project created successfully!\n$(RESET)"

# --- SINGLE UNIFIED COMPILATION RULE ---
$(OBJ_DIR): | $(MLX_LIB)
$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	$(SILENT)$(MKDIR) -p $(@D)
	$(SILENT)printf "$(YELLOW)Compiling:$(RESET) $(CYAN)%-35s$(RESET)\n" $<
	$(SILENT)$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# --- LIBRARY RULES ---
$(LIBFT):
	$(SILENT)printf "\n"
	$(SILENT)printf "$(BLUE_BOLD)Building dependency: libft...$(RESET)\n"
	$(SILENT)$(MAKE) -s -C $(LIBFT_DIR)
	$(SILENT)printf "$(GREEN)✓ Dependency built: libft\n$(RESET)"

$(MLX_LIB): $(MLX_DIR)
	$(SILENT)printf "$(BLUE_BOLD)Building dependency: MiniLibX...$(RESET)\n"
	$(SILENT)$(MAKE) -s -C $(MLX_DIR) >/dev/null 2>&1
	$(SILENT)printf "$(GREEN)✓ Dependency built: MiniLibX\n$(RESET)"

$(MLX_DIR):
	$(SILENT)printf "$(BLUE_BOLD)Cloning dependency: MiniLibX...$(RESET)\n"
	$(SILENT)git clone --depth 1 $(MLX_GIT_REPO) $(MLX_DIR)

# --- CLEAN RULES ---
clean:
	$(SILENT)$(RM) -rf $(OBJ_DIR)
	$(SILENT)$(MAKE) -s -C $(LIBFT_DIR) clean
	$(SILENT)@[ -d $(MLX_DIR) ] && $(MAKE) -s -C $(MLX_DIR) clean >/dev/null 2>&1 || true
	$(SILENT)printf "$(YELLOW)Project object files cleaned.\n$(RESET)"

fclean:
	$(SILENT)$(RM) -rf $(OBJ_DIR)
	$(SILENT)$(RM) -f $(NAME)
	$(SILENT)$(MAKE) -s -C $(LIBFT_DIR) fclean
	$(SILENT)$(RM) -rf $(MLX_DIR)
	$(SILENT)printf "$(GREEN)Full clean complete.\n$(RESET)"

re:
	$(SILENT)$(MAKE) fclean --no-print-directory
	$(SILENT)$(MAKE) all --no-print-directory

.PHONY: all bonus clean fclean re
.SECONDARY:
.DELETE_ON_ERROR:
