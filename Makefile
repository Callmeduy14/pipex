# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/23 16:32:00 by yyudi             #+#    #+#              #
#    Updated: 2025/08/23 16:53:39 by yyudi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRC_DIR		= src
OBJ_DIR		= obj
B_OBJ_DIR	= obj_bonus
LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a
INCS	 	= -Iincludes -I$(LIBFT_DIR) -Isrc

VPATH	 	= $(SRC_DIR)

# Sumber (tanpa path)
SRCS_COMMON	= exec.c path.c split_quotes.c utils.c error.c split_quotes_helpers.c split_quotes_utils.c
SRCS_MAND	= main.c pipeline.c
SRCS_BONUS	= main_bonus.c pipeline_bonus.c here_doc_bonus.c pipeline_loop_bonus.c utils_bonus.c

# Object mapping
OBJS		= $(SRCS_COMMON:%.c=$(OBJ_DIR)/%.o) $(SRCS_MAND:%.c=$(OBJ_DIR)/%.o)
B_OBJS		= $(SRCS_COMMON:%.c=$(B_OBJ_DIR)/%.o) $(SRCS_BONUS:%.c=$(B_OBJ_DIR)/%.o)

# Default
all		: $(NAME)

# Link
$(NAME)	: $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT_A)

bonus	: $(LIBFT_A) $(B_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(B_OBJS) $(LIBFT_A)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(B_OBJ_DIR)/%.o: %.c | $(B_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJ_DIR) $(B_OBJ_DIR):
	mkdir -p $@

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJ_DIR) $(B_OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all bonus clean fclean re

