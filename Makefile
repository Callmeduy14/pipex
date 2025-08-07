NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iincludes -Ilibft
LIBFT = libft/libft.a

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c \
        $(SRC_DIR)/execute.c \
        $(SRC_DIR)/utils.c \
        $(SRC_DIR)/error_utils.c

OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C libft

clean:
	rm -rf $(OBJ_DIR)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re