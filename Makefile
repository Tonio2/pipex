NAME	=	pipex

CFLAGS	=	-Wall -Werror -Wextra -I ./includes -g

SDIR	=	srcs
_SRCS	=	main.c	\
			utils.c
SRCS	=	$(patsubst %, $(SDIR)/%, $(_SRCS))

ODIR	=	.objs
_OBJS	=	$(_SRCS:.c=.o)
OBJS	=	$(patsubst %, $(ODIR)/%, $(_OBJS))

NAME_B	=	pipex_bonus

SDIR_B	=	srcs_bonus
_SRCS_B	=	main_bonus.c	\
			utils_bonus.c	\
			gnl.c
SRCS_B	=	$(patsubst %, $(SDIR_B)/%, $(_SRCS_B))

ODIR_B	=	.objs_bonus
_OBJS_B	=	$(_SRCS_B:.c=.o)
OBJS_B	=	$(patsubst %, $(ODIR_B)/%, $(_OBJS_B))

all: $(NAME)

$(NAME): .objs $(OBJS)
	make -C ./libft
	gcc $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

.objs:
	mkdir .objs

$(ODIR)/%.o: $(SDIR)/%.c
	gcc -c $(CFLAGS) $^ -o $@

bonus: $(NAME_B)

$(NAME_B): .objs_bonus $(OBJS_B)
	make -C ./libft
	gcc $(CFLAGS) $(OBJS_B) ./libft/libft.a -o $(NAME_B)

.objs_bonus:
	mkdir .objs_bonus

$(ODIR_B)/%.o: $(SDIR_B)/%.c
	gcc -c $(CFLAGS) $^ -o $@

clean:
	make clean -C ./libft
	rm -f $(OBJS)
	rm -f $(OBJS_B)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)
	rm -f $(NAME_B)

re: fclean all
