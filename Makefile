# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 17:59:50 by fyudris           #+#    #+#              #
#    Updated: 2025/06/12 18:00:03 by fyudris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



	
# Executable Name
#
NAME = so_long

#
# Compiler and Flags
#
CC = cc
CFLAGS = -Wall -Wextra -Werror
# Add this flag to tell the compiler where to find your header files
# -Iinclude tells it to look in your 'include' folder for so_long.h
# -Ilibft/includes tells it to look in your libft's include folder
# -Imlx_linux tells it to look in the mlx_linux folder for mlx.h
INC_FLAGS = -Iinclude -Ilibft/includes -Imlx_linux

#
# Directories
#
SRC_DIR = srcs
OBJ_DIR = obj
LIBFT_DIR = libft
MLX_DIR = mlx_linux

#
# Source Files
#
SRCS = $(addprefix $(SRC_DIR)/, main.c)
# Add more .c files from your srcs directory here as you create them

#
# Object Files
#
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

#
# Libraries
#
# Path to your libft.a
LIBFT = $(LIBFT_DIR)/libft.a
# Path to your mlx library and its linker flags
MLX = $(MLX_DIR)/libmlx_Linux.a
# These are the libraries that mlx needs to work on Linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

#
# Main compilation rule
#
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

#
# Rule to build object files
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

#
# Create the object directory
#
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

#
# Rules to build libraries
#
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# This rule assumes there's a Makefile inside mlx_linux that builds the library.
# If libmlx_Linux.a is already there, it will just use it.
$(MLX):
	$(MAKE) -C $(MLX_DIR)

#
# Clean-up rules
#
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

#
# Phony targets to prevent conflicts with file names
#
.PHONY: all clean fclean re