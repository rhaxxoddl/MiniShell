

NAME	=	Libft.a

CC		=	gcc
AR		=	ar rcs
CF		=	-Wall -Wextra -Werror

SRC		=	ft_split.c\
			ft_memset.c\
			ft_bzero.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memccpy.c\
			ft_memchr.c\
			ft_strlen.c\
			ft_strlcpy.c\
			ft_memcmp.c\
			ft_strlcat.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strnstr.c\
			ft_strncmp.c\
			ft_strcmp.c\
			ft_atoi.c\
			ft_atol.c\
			ft_isalpha.c\
			ft_isdigit.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_isspace.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_strcmp.c
BSRC	=	ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c
OBJ		=	$(SRC:.c=.o)
BOBJ	=	$(BSRC:.c=.o)

all		:	$(NAME)

bonus	:	$(BOBJ) $(NAME)
	$(AR) $(NAME) $(BOBJ)

$(NAME)	:	$(OBJ)
	$(AR) $@ $(OBJ)

%.o		:	%.c
	$(CC) $(CF) -c $<

clean	:
	rm -f $(OBJ) $(BOBJ)

fclean	:		clean
	rm -f $(bonus) $(NAME) 

re		:		fclean all

.PHONY	:	clean fclean re
