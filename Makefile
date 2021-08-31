NAME	=	pipex

CFLAGS	=	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): main.o utils.o
	make -C ./libft
	gcc $(CFLAGS) main.o utils.o ./libft/libft.a -o $(NAME)

.c.o:
	gcc -c $(CFLAGS) $^ -o $@

clean:
	make clean -C ./libft
	rm -f main.o

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all
