SRC			=	src/*.c
LIBFTDIR	=	include/Libft
PRINTFDIR	=	include/ft_printf

LIBS		=	$(LIBFTDIR)/libft.a $(PRINTFDIR)/libftprintf.a

OBJS		=	$(SRC:.c=.o)

CC 			=	CC
RM			=	rm -f
FLAGS		=	-Wall -Wextra -Werror

NAME		= pipex

all:		$(NAME)
$(NAME):	$(OBJS)
			make -sC $(LIBFTDIR)
			make -sC $(PRINTFDIR)
			$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
			$(RM) $(OBJS)
			make --no-print-directory -sC $(LIBFTDIR) clean
			make --no-print-directory -sC $(PRINTFDIR) clean

fclean:		clean
			$(RM) $(NAME)
			make --no-print-directory -sC $(LIBFTDIR) fclean
			make --no-print-directory -sC $(PRINTFDIR) fclean

re: 		fclean all

.PHONY:		all clean fclean re