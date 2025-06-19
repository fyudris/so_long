# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 17:59:50 by fyudris           #+#    #+#              #
#    Updated: 2025/06/19 15:28:53 by fyudris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# === CONFIGURATION ===
NAME            := so_long
CC              := cc
RM              := rm -f
MKDIR           := /bin/mkdir -p

# === DIRECTORIES ===
OBJ_DIR         := obj
SRC_DIR         := srcs
INC_DIR         := include
LIBFT_DIR       := libft
MLX_DIR         := mlx_linux

# === LIBRARIES ===
LIBFT           := $(LIBFT_DIR)/libft.a
MLX_FLAGS       := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# === FLAGS ===
CFLAGS          := -Wall -Wextra -Werror -g
CPPFLAGS        := -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR) -MD

# === SOURCE FILES (Listed with vpath) ===
SRCS            :=
# --- Main Files ---
vpath %.c $(SRC_DIR)
SRCS            += main.c

# --- Initialization Files ---
vpath %.c $(SRC_DIR)/init
SRCS            += init.c
SRCS            += memory.c

# --- Game Logic Files ---
vpath %.c $(SRC_DIR)/game
SRCS            += hooks.c
SRCS            += logic.c

# --- Parsing Files ---
vpath %.c $(SRC_DIR)/parsing
SRCS            += parse_map.c
SRCS            += validate_content.c
SRCS            += validate_path.c

# --- Rendering Files ---
vpath %.c $(SRC_DIR)/rendering
SRCS            += render.c
SRCS            += image.c
SRCS            += textures.c

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

$(NAME): $(OBJS) $(LIBFT) $(MLX_DIR)/libmlx.a
	@printf "$(BLUE_BOLD)Linking executable:$(RESET) $@\n"
	@$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@printf "$(GREEN)✓ Project '$@' created successfully!$(RESET)\n"

# This rule now works with vpath to find the source files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(MKDIR) -p $(@D)
	@printf "$(YELLOW)Compiling:$(RESET) $<\n"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(MKDIR) -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	@$(MAKE) -s -C $(MLX_DIR)

# --- CLEAN RULES ---
clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(YELLOW)✓ Object files cleaned.\n$(RESET)"

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(RM) -f $(NAME)
	@printf "$(GREEN)✓ Final clean complete.\n$(RESET)"

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

# --- NORMINETTE RULE ---
norminette:
	@echo "Checking C files in srcs/, include/, and libft/ for norm compliance..."
	@norminette srcs/ include/ libft/

.PHONY: all clean fclean re
.SECONDARY:
.DELETE_ON_ERROR: