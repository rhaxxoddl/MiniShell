TARGET	=	parsing

DEBUG	=	parsing_d
CC		=	clang

INC_DIR		=	../../includes
LIB_NAME	=	Libft
LIB_DIR		=	../../includes/Libft
RL_DIR		=	./readline-master

AR			= 	ar rc
CFLAGS		=	-Wall -Wextra -Werror
DEBUGFLAG	= -fsanitize=address -g3
LDFLAGS		=	-lc -lreadline

SRCS		=	./main.c\
				./free.c\
				./init.c\
				./parsing_env.c\
				./parsing_quotes.c\
				./parsing_util.c\
				./parsing.c\
				./parsing_redir.c
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


.PHONY	: clean fclean dclean d all re Libft parsing
