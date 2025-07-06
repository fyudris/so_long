# === EXECUTABLE NAMES ===
NAME            := so_long
NAME_BONUS      := so_long

# === CONFIGURATION ===
CC              := cc
RM              := rm -f
MKDIR           := /bin/mkdir -p

# === OS DETECTION ===
OS              := $(shell uname -s)

# === DIRECTORIES ===
OBJ_DIR_MAND    := obj/mandatory
OBJ_DIR_BONUS   := obj/bonus
LIBFT_DIR       := libft
MLX_DIR         := minilibx
INC_DIR         := include
SRC_DIRS        := srcs srcs/init srcs/parsing srcs/game srcs/rendering srcs/utils

# === LIBRARIES ===
LIBFT           := $(LIBFT_DIR)/libft.a
MLX_LIB         := $(MLX_DIR)/libmlx.a

# === FLAGS & OS-SPECIFIC SETTINGS ===
CFLAGS          := -Wall -Wextra -Werror -g -MD
BONUS_FLAG      := -DBONUS_PART=1
CPPFLAGS        := -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)
LDFLAGS         := -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS          := -lft -lmlx -lXext -lX11 -lm

# --- Set MiniLibX git repo and linker flags based on OS ---
ifeq ($(OS), Linux)
    MLX_GIT_REPO := https://github.com/42Paris/minilibx-linux.git
else ifeq ($(OS), Darwin)
    MLX_GIT_REPO := https://github.com/42Paris/minilibx-linux.git
    LDFLAGS      += -L/opt/X11/lib
endif

# === SOURCE & OBJECT FILES ===
vpath %.c $(SRC_DIRS)
# --- Mandatory files ---
MANDATORY_SRCS  := main.c image.c image_utils.c time.c \
                   init.c memory.c parse_map.c validate_content.c \
                   validate_path.c hooks.c render.c textures.c
OBJS_MANDATORY  := $(addprefix $(OBJ_DIR_MAND)/, $(MANDATORY_SRCS:.c=.o))

# --- Bonus files (RESTORED) ---
BONUS_SRCS      := main.c image.c image_utils.c time.c \
                   init_bonus.c memory_bonus.c parse_map.c \
                   validate_content_bonus.c validate_path_bonus.c \
                   hooks_bonus.c render_bonus.c textures_bonus.c logic.c \
                   hooks_utils_bonus.c render_utils_bonus.c \
                   textures_utils_bonus.c render_ui_bonus.c
OBJS_BONUS      := $(addprefix $(OBJ_DIR_BONUS)/, $(BONUS_SRCS:.c=.o))

# Dependency files for header changes
DEPS            := $(OBJS_MANDATORY:.o=.d) $(OBJS_BONUS:.o=.d)

# === MAIN RULES ===
.DEFAULT_GOAL   := all
all: $(NAME)

-include $(DEPS)

# --- TARGETS ---
$(NAME): $(OBJS_MANDATORY) $(LIBFT) $(MLX_LIB)
	@printf "\033[1;34mLinking executable:\033[0m $(NAME)\n"
	@$(CC) $(OBJS_MANDATORY) -o $(NAME) $(LDFLAGS) $(LDLIBS)
	@printf "\033[0;32m✓ Mandatory project '$(NAME)' created successfully!\033[0m\n"

# --- Bonus Target (RESTORED) ---
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX_LIB)
	@printf "\033[1;34mLinking BONUS executable:\033[0m $(NAME_BONUS)\n"
	@$(CC) $(OBJS_BONUS) -o $(NAME_BONUS) $(LDFLAGS) $(LDLIBS)
	@printf "\033[0;32m✓ Bonus project '$(NAME_BONUS)' created successfully!\033[0m\n"

# --- COMPILATION RULES ---
# --- Mandatory Rule ---
$(OBJ_DIR_MAND): | $(MLX_LIB)
$(OBJ_DIR_MAND)/%.o: %.c $(OBJ_DIR_MAND)
	@$(MKDIR) -p $(@D)
	@printf "\033[0;33mCompiling [MANDATORY]:\033[0m $<\n"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# --- Bonus Rule (RESTORED) ---
$(OBJ_DIR_BONUS): | $(MLX_LIB)
$(OBJ_DIR_BONUS)/%.o: %.c $(OBJ_DIR_BONUS)
	@$(MKDIR) -p $(@D)
	@printf "\033[0;33mCompiling [BONUS]:\033[0m $<\n"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(BONUS_FLAG) -c $< -o $@

# --- LIBRARY RULES ---
$(LIBFT):
	@printf "\033[1;34mBuilding libft...\033[0m\n"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX_LIB): $(MLX_DIR)
	@printf "\033[1;34mBuilding MiniLibX...\033[0m\n"
	@$(MAKE) -s -C $(MLX_DIR)
	@printf "\033[0;32m✓ MiniLibX built successfully\033[0m\n"

$(MLX_DIR):
	@printf "\033[1;34mCloning MiniLibX from git...\033[0m\n"
	@git clone --depth 1 $(MLX_GIT_REPO) $(MLX_DIR)

# --- CLEAN RULES ---
clean:
	@printf "\033[0;33mCleaning object files...\033[0m\n"
	@$(RM) -rf obj
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@[ -d $(MLX_DIR) ] && $(MAKE) -s -C $(MLX_DIR) clean >/dev/null 2>&1 || true

fclean: clean
	@printf "\033[0;32mCleaning up everything...\033[0m\n"
	@$(RM) -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(RM) -rf $(MLX_DIR)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all bonus clean fclean re
.SECONDARY:
.DELETE_ON_ERROR:
