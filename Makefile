CC			=	gcc
CC_FLAGS	=	-Wall -Wextra -Werror 
RM			=	rm -rf
DIR_HEADERS =	./includes/
HEADER			= includes/minishell.h
LIBFT_DIR		= libs/libft/
LIBFT 			= $(LIBFT_DIR)libft.a
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./compiled_srcs/
SRC			=	main.c builtins.c cd.c heredoc.c\
				export_utils.c export.c\
				file_checker.c\
				var_keeper.c utils.c\
				echo.c signal.c art.c\
				ft_split_our.c parse_output.c\
				parse_input.c init.c utils1.c\
				utils2.c env.c


NORMINETTE	:=	$(shell which norminette)

ifeq (, $(shell which norminette))
	NORMINETTE := ${HOME}/.norminette/norminette.rb
endif


SRCS		=	$(SRC)
OBJS 		=	$(SRCS:%.c=$(DIR_OBJS)%.o)
NAME 		=	minishell

ifeq ($(USER), letumany)
    LDFLAGS		=	-L /Users/letumany/lib 
	CPPFLAGS 	=	-I /Users/letumany/include
else ifeq ($(USER), amidoyan)
	LDFLAGS		=	-L /Users/amidoyan/lib 
	CPPFLAGS 	=	-I /Users/amidoyan/include
else 
	LDFLAGS		=	-L /usr/local/opt/readline/lib 
	CPPFLAGS 	=	-I /usr/local/opt/readline/include
endif

all:			$(NAME)

debug:			CC_FLAGS += -g3 -fsanitize=address
debug:			all

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				@tput setaf 190 && printf "\033[2K\rCompiling $<"
				@$(CC) $(CC_FLAGS) $(CPPFLAGS) -I $(DIR_HEADERS) -c $< -o $@

$(NAME):		$(OBJS) $(HEADER)
				@make -C $(LIBFT_DIR)
				@tput setaf 2 && printf "\033[2K\r.o compiled.\n"
				@$(CC) $(CC_FLAGS)  -L $(LIBFT_DIR) -lft -I $(DIR_HEADERS) -lncurses $(LDFLAGS) -lreadline $(OBJS) -o $(NAME)
				@tput setaf 2 && printf "$(NAME) created.\n"
				@tput setaf 255

$(OBJS):		| $(DIR_OBJS)


$(DIR_OBJS):
				@mkdir $@

clean:
				@$(RM) $(DIR_OBJS)
				@make clean -C $(LIBFT_DIR)
				@tput setaf 928 && printf ".o deleted.\n"
				@tput setaf 255

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT_DIR)
				@tput setaf 928 && printf ""$(NAME)" deleted.\n"
				@tput setaf 255

re:				fclean all

me:				all
				@./minishell

norm:
				@$(NORMINETTE) $(DIR_SRCS)
				@$(NORMINETTE) $(DIR_HEADERS)

.PHONY:			all clean fclean re me debug norm