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


SRV		=	server
CLT		=	client

COMOBJ	=	utils.o
SRVOBJ	=	server.o server_utils.o
CLTOBJ	=	client.o
CFLAGS	=	-Wall -Wextra -Werror
# CFLAGS	=	-g -fsanitize=address
RM		=	rm -rf

all		: $(SRV) $(CLT)

# BUFFER and BAUD can't be modified this way, 
# the object files are made with the preset values anyway,
# would need to add the same check to their creation. 
$(SRV)	: $(SRVOBJ) $(COMOBJ)
ifdef BUFFER
	$(CC) -D BUFFER=$(BUFFER) -o $(@) $(CFLAGS) $(SRVOBJ) $(COMOBJ) -I.
else
	$(CC) -o $(@) $(CFLAGS) $(SRVOBJ) $(COMOBJ) -I.
endif

$(CLT)	: $(CLTOBJ) $(COMOBJ)
ifdef BAUD
	$(CC) -o $(@) $(CFLAGS) $(CLTOBJ) $(COMOBJ) -I. -D BAUD=$(BAUD)
else
	$(CC) -o $(@) $(CFLAGS) $(CLTOBJ) $(COMOBJ) -I.
endif

clean	:
	$(RM) $(SRVOBJ) $(CLTOBJ) $(COMOBJ)

fclean	: clean
	$(RM) $(SRV) $(CLT)

bonus	: all

re		: fclean all

.PHONY : all clean fclean re bonus $(SRV) $(CLT)