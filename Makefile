NAME	=	pipex

CFLAGS	=	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): main.o
	gcc $(CFLAGS) main.o -o $(NAME)

.c.o:
	gcc -c $(CFLAGS) $^ -o $@

clean:
	rm -f main.o

fclean: clean
	rm -f $(NAME)

re: fclean all
