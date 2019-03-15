NAME = fillit

SRCS = main.c fillit.c map.c support.c save_piece.c 
OBJS = $(SRCS:.c=.o) libft.a

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -c $(SRCS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
