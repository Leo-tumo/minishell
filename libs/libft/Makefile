
.PHONY: all clean fclean re

NAME		= libft.a
HEADER		= libft.h
SRCS		= $(wildcard *.c)
OBJS		= $(SRCS:.c=.o)
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
AR			= ar csr


$(NAME) : $(OBJS) $(HEADER)
	@$(AR) $(NAME) $(OBJS)

%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	@tput setaf 190 && printf "\033[2K\rCompiling $<"

all : $(NAME)

clean :
	@$(RM) *.o
	

fclean : clean
	@$(RM) $(NAME)

re : fclean all 

