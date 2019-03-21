NAME = fillit

SRC = main.c fillit.c map.c support.c save_piece.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ): 
		@gcc -c -Wall -Werror -Wextra $(SRC)

$(NAME): LIB $(OBJ)
	@gcc $(OBJ) ./libft/libft.a -o $(NAME)

LIB:
	@$(MAKE) -C ./libft/

clean:
	/bin/rm -f $(OBJ)
	@$(MAKE) -C ./libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	@$(MAKE) -C ./libft/ fclean

re: fclean all
