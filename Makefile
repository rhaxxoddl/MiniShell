TARGET	=	minishell

DEBUG	=	minishell_d
CC		=	clang

INC_DIR		=	./includes
LIB_NAME	=	Libft
LIB_DIR		=	./includes/Libft
RL_DIR		=	./readline-master

AR			= 	ar rc
CFLAGS		=	-Wall -Wextra -Werror
RLFLAGS		=	-I${HOME}/.brew/opt/readline/include
DEBUGFLAG	= -fsanitize=address -g3
LDFLAGS		=	-lc -lreadline -L${HOME}/.brew/opt/readline/lib

SRCS		=	$(SYSTEM_DIR)/main.c\
				$(SYSTEM_DIR)/run_cmd.c\
				$(SYSTEM_DIR)/error.c\
				$(SYSTEM_DIR)/redirection.c\
				$(SYSTEM_DIR)/here_doc_util.c\
				$(SYSTEM_DIR)/connect_cmd.c\
				$(SYSTEM_DIR)/exec_cmd.c\
				$(SYSTEM_DIR)/signal_handler.c\
				$(PARSING_DIR)/free.c\
				$(PARSING_DIR)/init.c\
				$(PARSING_DIR)/parsing.c\
				$(PARSING_DIR)/parsing_env.c\
				$(PARSING_DIR)/parsing_quotes.c\
				$(PARSING_DIR)/parsing_redir.c\
				$(PARSING_DIR)/parsing_util.c\
				$(BUILTIN_DIR)/builtin_utils.c\
				$(BUILTIN_DIR)/ft_cd.c\
				$(BUILTIN_DIR)/ft_echo.c\
				$(BUILTIN_DIR)/ft_env.c\
				$(BUILTIN_DIR)/ft_exit.c\
				$(BUILTIN_DIR)/ft_export_print.c\
				$(BUILTIN_DIR)/ft_export.c\
				$(BUILTIN_DIR)/ft_pwd.c\
				$(BUILTIN_DIR)/ft_unset.c
SRC_DIR		=	./src
PARSING_DIR	=	$(SRC_DIR)/parsing
SYSTEM_DIR	=	$(SRC_DIR)/system
BUILTIN_DIR	=	$(SRC_DIR)/builtin
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


.PHONY	: clean fclean dclean d all re Libft
