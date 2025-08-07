NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard ft_*.c)
OBJ = $(SRC:.c=.o)
HEADER = libft.h

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 