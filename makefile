# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 20:15:48 by znichola          #+#    #+#              #
#    Updated: 2022/11/21 20:15:48 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRVNM = server
CLTNM = client

COMOBJ = utils.o
SRVOBJ = server.o
CLTOBJ = client.o
# CFLAGS = -Wall -Werror -Wextra
CFLAGS = -g

all : $(SRVNM) $(CLTNM)

$(SRVNM) : $(SRVOBJ) $(COMOBJ)
	$(CC) -o $(@) $(CFLAGS) $(SRVOBJ) $(COMOBJ) -I.

$(CLTNM) : $(CLTOBJ) $(COMOBJ)
	$(CC) -o $(@) $(CFLAGS) $(CLTOBJ) $(COMOBJ) -I.

clean :
	$(RM) $(SRVOBJ) $(CLTOBJ)

fclean : clean
	$(RM) $(SRVNM) $(CLTOBJ)

re : fclean all

.PHONY : all clean fclean re