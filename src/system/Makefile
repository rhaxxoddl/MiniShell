TARGET	=	pipex

DEBUG	=	pipex_d
CC		=	clang

INC_DIR		=	../../includes
LIB_NAME	=	Libft
LIB_DIR		=	../../includes/Libft

AR			= 	ar rc
CFLAGS		=	-Wall -Wextra -Werror
DEBUGFLAG	= -fsanitize=address -g3
LDFLAGS		=	-lc

SRCS		=	./main.c\
				./pipe.c\
				./error.c\
				./cmd.c\
				./parsing.c\
				./ft_split_p.c\
				./path.c\
				./redirection.c\
				./free_array.c\
				./free_struct.c
SRCS_DIR	=	./
OBJS		=	$(SRCS:.c=.o)
ARFS		=	$(LIB_DIR)/Libft.a
MAKEFLAGS	+=	--silent

all		:	$(TARGET)

d		:	$(DEBUG)

$(TARGET)	:	$(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(ARFS) -o $@ $^

.c.o	:
	brew install readline
	$(CC) $(CFLAGS) -I $(LIB_DIR) -I $(INC_DIR) -c $< -o $@


$(DEBUG)	:	$(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(ARFS) $(DEBUGFLAG) -o $@ $^

fclean	:	clean
	rm -f $(TARGET)
	rm -f *.a
	make -C $(LIB_DIR) fclean

dclean	:	fclean
	rm -f $(DEBUG)

clean	:
	rm -f $(OBJS)
	make -C $(LIB_DIR) clean

re		:	fclean all


.PHONY	: clean fclean dclean d all re Libft pipex
