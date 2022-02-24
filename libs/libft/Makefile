# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: letumany <letumany@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 20:20:25 by letumany          #+#    #+#              #
#    Updated: 2021/08/01 21:59:05 by letumany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

all : $(NAME)

clean :
	@$(RM) *.o
	

fclean : clean
	@$(RM) $(NAME)

re : fclean all 

