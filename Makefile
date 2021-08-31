NAME	=	pipex

CFLAGS	=	-Wall -Werror -Wextra -I ./includes -g

SDIR	=	srcs
_SRCS	=	main.c	\
			utils.c
SRCS	=	$(patsubst %, $(SDIR)/%, $(_SRCS))

ODIR	=	.objs
_OBJS	=	$(_SRCS:.c=.o)
OBJS	=	$(patsubst %, $(ODIR)/%, $(_OBJS))

all: $(NAME)

$(NAME): .objs $(OBJS)
	make -C ./libft
	gcc $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

.objs:
	mkdir .objs

$(ODIR)/%o: $(SDIR)/%c
	gcc -c $(CFLAGS) $^ -o $@

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all
