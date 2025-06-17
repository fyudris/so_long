# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 17:59:50 by fyudris           #+#    #+#              #
#    Updated: 2025/06/17 02:10:15 by fyudris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- CONFIG ---
NAME            := so_long
CC              := cc
RM              := /bin/rm -f
MKDIR           := /bin/mkdir -p

# --- DIRECTORIES ---
OBJ_DIR         := obj
SRC_DIR         := srcs
INC_DIR         := include
LIBFT_DIR       := libft
MLX_DIR         := mlx_linux

# --- FLAGS ---
CFLAGS          := -Wall -Wextra -Werror
CPPFLAGS        := -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)
# The -MD flag generates dependency files automatically
CPPFLAGS        += -MD

# --- LIBRARIES ---
# MiniLibX flags for linking
MLX_FLAGS       := -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
# Libft library path
LIBFT           := $(LIBFT_DIR)/libft.a

# --- SOURCE FILES ---
# Automatically find all .c files in the source directory and subdirectories
SRCS            := $(shell find $(SRC_DIR) -name '*.c')

# --- OBJECT FILES ---
# Generate object file paths from source file paths
OBJS            := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# --- DEPENDENCIES ---
# Include the generated dependency files
DEPS            := $(OBJS:.o=.d)
-include $(DEPS)

# --- COLORS (for pretty printing) ---
GREEN           := \033[0;32m
YELLOW          := \033[0;33m
RESET           := \033[0m

# --- TARGETS ---
.DEFAULT_GOAL   := all

all: $(NAME)

# Link the final executable
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@printf "$(GREEN)✓ Project '$@' created successfully!$(RESET)\n"

# Compile object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@printf "$(YELLOW)Compiling:$(RESET) %s\n" $<
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

# Build the libft library using its own Makefile
$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

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

.PHONY: all clean fclean re
.SECONDARY:
.DELETE_ON_ERROR: