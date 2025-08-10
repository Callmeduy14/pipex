# **************************************************************************** #
#                                   PIPEX                                      #
# **************************************************************************** #

NAME		:= pipex
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
AR			:= ar rcs
RM			:= rm -f

SRC_DIR		:= src
INC_DIR		:= includes
OBJ_DIR		:= obj

SRCS := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/error.c \
	$(SRC_DIR)/path.c \
	$(SRC_DIR)/split_quotes.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/here_doc.c \
	$(SRC_DIR)/exec.c \
	$(SRC_DIR)/pipeline.c

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR	:= libft
LIBFT_A		:= $(LIBFT_DIR)/libft.a

INCS := -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/pipex.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

all: $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
