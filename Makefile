SERV	=	server

CLI		=	client

SSERV	=	server.c

SCLI	=	client.c

SUTILS	=	utils.c

OBJS_C = $(SCLI:.c=.o)

OBJS_S = $(SSERV:.c=.o)

GREEN		= \033[1;32m

DEFAULT		= \033[0m

FLAGS	=	-Wall -Wextra -Werror -g3

CC		= 	cc

all : server client

server :
$(SERV) : $(OBJS_S)
	$(CC) $(FLAGS) $(OBJS_S) $(SUTILS) -o $(SERV)

client:
$(CLI) : $(OBJS_C)
	$(CC) $(FLAGS) $(OBJS_C) $(SUTILS) -o $(CLI)

clean :
	rm -rf $(OBJS_C) $(OBJS_S)

fclean : 	clean
	rm -rf $(SERV) $(CLI)
	@echo "\n${GREEN}Everything cleaned${DEFAULT}"

re :
	make fclean
	make all

.PHONY : re clean fclean all