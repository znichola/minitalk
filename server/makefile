# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 14:49:07 by znichola          #+#    #+#              #
#    Updated: 2022/11/21 14:49:07 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server

OBJS = main.o server.o

# CFLAGS = -Wall -Werror -Wextra
CFLAGS = -g

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) -I.

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re