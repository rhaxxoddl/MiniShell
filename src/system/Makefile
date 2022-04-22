TARGET	=	pipex

DEBUG	=	pipex_d
CC		=	clang

INC_DIR		=	../../includes
LIB_NAME	=	Libft
LIB_DIR		=	../../includes/Libft
RL_DIR		=	./readline-master

AR			= 	ar rc
CFLAGS		=	-Wall -Wextra -Werror
RLFLAGS		=	-I${HOME}/.brew/opt/readline/include
DEBUGFLAG	= -fsanitize=address -g3
LDFLAGS		=	-lc -lreadline -L${HOME}/.brew/opt/readline/lib

SRCS		=	./main.c\
				./run_cmd.c\
				./error.c\
				./parsing.c\
				./redirection.c\
				./here_doc_util.c\
				./signal_handler.c
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
	$(CC) $(CFLAGS) -I $(LIB_DIR) $(RLFLAGS) -I $(INC_DIR) -c $< -o $@


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
