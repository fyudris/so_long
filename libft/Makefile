# Makefile for libft (Linux/macOS compatible)

# Config
NAME			:=	libft.a

# Directories
INC_DIR			:=	includes
SRC_DIR			:=	srcs
OBJ_DIR			:=	obj

# Tools
CC				:=	cc
AR				:=	ar rcs
RM				:=	/bin/rm -f
MKDIR			:=	/bin/mkdir -p

# Flags
CFLAGS			:=	-Wall -Wextra -Werror
CPPFLAGS		:=	-I$(INC_DIR)
CPPFLAGS		+=	-MD

# Sources
SRC				:=
vpath %.c $(SRC_DIR)/ft_is
SRC				+=	ft_isalnum.c
SRC				+=	ft_isalpha.c
SRC				+=	ft_isascii.c
SRC				+=	ft_isdigit.c
SRC				+=	ft_isprint.c

vpath %.c $(SRC_DIR)/ft_lst
SRC				+=	ft_lstadd_back_bonus.c
SRC				+=	ft_lstdelone_bonus.c
SRC				+=	ft_lstmap_bonus.c
SRC				+=	ft_lstadd_front_bonus.c
SRC				+=	ft_lstiter_bonus.c
SRC				+=	ft_lstnew_bonus.c
SRC				+=	ft_lstclear_bonus.c
SRC				+=	ft_lstlast_bonus.c
SRC				+=	ft_lstsize_bonus.c

vpath %.c $(SRC_DIR)/ft_mem
SRC				+=	ft_bzero.c
SRC				+=	ft_calloc.c
SRC				+=	ft_memchr.c
SRC				+=	ft_memcmp.c
SRC				+=	ft_memcpy.c
SRC				+=	ft_memmove.c
SRC				+=	ft_memset.c
SRC				+=	ft_free_array.c
SRC				+=	ft_realloc.c

vpath %.c $(SRC_DIR)/ft_put
SRC				+=	ft_putchar_fd.c
SRC				+=	ft_putendl_fd.c
SRC				+=	ft_putnbr_fd.c
SRC				+=	ft_putstr_fd.c

vpath %.c $(SRC_DIR)/ft_str
SRC				+=	ft_split.c
SRC				+=	ft_strchr.c
SRC				+=	ft_strdup.c
SRC				+=	ft_striteri.c
SRC				+=	ft_strjoin.c
SRC				+=	ft_strlcat.c
SRC				+=	ft_strlcpy.c
SRC				+=	ft_strlen.c
SRC				+=	ft_strmapi.c
SRC				+=	ft_strncmp.c
SRC				+=	ft_strnstr.c
SRC				+=	ft_strrchr.c
SRC				+=	ft_strtrim.c
SRC				+=	ft_substr.c

vpath %.c $(SRC_DIR)/ft_to
SRC				+=	ft_atoi.c
SRC				+=	ft_itoa.c
SRC				+=	ft_tolower.c
SRC				+=	ft_toupper.c
SRC				+=	ft_atol.c

vpath %.c $(SRC_DIR)/ft_printf
SRC				+=	ft_print_char.c
SRC				+=	ft_printf.c
SRC				+=	ft_print_hex.c
SRC				+=	ft_print_int.c
SRC				+=	ft_print_pointer.c
SRC				+=	ft_print_str.c
SRC				+=	ft_print_unsigned_int.c

vpath %.c $(SRC_DIR)/ft_gnl
SRC             +=  get_next_line.c
SRC				+=	get_next_line_utils.c

# Object Files
OBJ			:=	$(SRC:.c=.o)
OBJ			:=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Dependencies
DEPS		:=	$(OBJ:.o=.d)
-include $(DEPS)

# Target
.DEFAULT_GOAL	:=	all

all: $(NAME)

# # --- PRETTY LIBRARY CREATION RULE (MODIFIED) ---
$(NAME): $(OBJ)
	@$(AR) $@ $^
	@printf "$(GREEN)✓ Library '$@' created successfully!\n$(RESET)"

# --- PRETTY COMPILATION RULE (MODIFIED) ---
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "$(YELLOW)Compiling:$(RESET) %s\n" $<
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# --- PRETTY DIRECTORY CREATION RULE (MODIFIED) ---
$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	@printf "$(BLUE_BOLD)Created object directory:$(RESET) $@\n"

# --- PRETTY CLEAN RULES (MODIFIED) ---
clean:
	@# The -r flag is for "recursive" to delete a directory.
	@# The -f flag is for "force" to ignore nonexistent files.
	@# We redirect errors to /dev/null and use '|| true' to prevent 'make' from
	@# stopping if the directory doesn't exist yet.
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(YELLOW)✓ Object files cleaned.\n$(RESET)"

fclean: clean
	@$(RM) -f $(NAME)
	@printf "$(GREEN)✓ Final clean complete. Library removed.\n$(RESET)"


re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re
.SECONDARY:
.DELETE_ON_ERROR: