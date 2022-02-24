CC			=	gcc
CC_FLAGS	=	-Wall -Wextra -Werror 
RM			=	rm -rf
DIR_HEADERS =	./includes/
HEADER			= includes/minishell.h
LIBFT_DIR		= libs/libft/
LIBFT 			= $(LIBFT_DIR)libft.a
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./compiled_srcs/
SRC			=	main.c	
SRCS		=	$(SRC)
OBJS 		=	$(SRCS:%.c=$(DIR_OBJS)%.o)
NAME 		=	minishell

all:			$(NAME)

debug:			CC_FLAGS += -g3 -fsanitize=address
debug:			all

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				@tput setaf 190 && printf "\033[2K\r Compiling $<"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@

$(NAME):		$(OBJS) $(HEADER)
				@make -C $(LIBFT_DIR)
				@tput setaf 2 && printf "\033[2K\r.o compiled.\n"
				@$(CC) $(CC_FLAGS)  -L $(LIBFT_DIR) -lft -I $(DIR_HEADERS) -l readline $(OBJS) -o $(NAME)
				@tput setaf 2 && printf "$(NAME) created.\n"

$(OBJS):		$(DIR_OBJS)


$(DIR_OBJS):
				@mkdir $@

clean:
				@$(RM) $(DIR_OBJS)
				@make clean -C $(LIBFT_DIR)
				@tput setaf 928 && printf ".o deleted.\n"

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT_DIR)
				@tput setaf 928 && printf ""$(NAME)" deleted.\n"

re:				fclean all

me:				all
				@./minishell


.PHONY:			all clean fclean re me debug
