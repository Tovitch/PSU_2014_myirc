##
## Makefile for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
## 
## Made by kruszk_t
## Login   <kruszk_t@epitech.net>
## 
## Started on  Thu Mar 26 17:45:51 2015 kruszk_t
## Last update Sat Jan 16 16:47:06 2016 Tony KRUSZKEWYCZ
##

SRC_S		= sources/main_server.c		\
		  sources/add_server.c		\
		  sources/add_client.c		\
		  sources/add_chan.c		\
		  sources/read_client.c		\
		  sources/send_list.c		\
		  sources/write_client.c	\
		  sources/send_accept_file.c	\
		  sources/send_msg.c		\
		  sources/list_users.c		\
		  sources/join_part_chan.c	\
		  sources/my_str_to_wordtab.c	\

NAME_S		= server

OBJ_S		= $(SRC_S:.c=.o)

SRC_C		= sources/main_client.c		\
		  sources/run_clt.c		\
		  sources/cmd_server.c		\
		  sources/cmd_nick.c		\
		  sources/cmd_list.c		\
		  sources/cmd_join_part.c	\
		  sources/cmd_users.c		\
		  sources/cmd_msg.c		\
		  sources/cmd_sendFile.c	\
		  sources/cmd_acceptFile.c	\
		  sources/add_chan.c		\
		  sources/my_str_to_wordtab.c	\
		  sources/my_strdup.c

NAME_C		= client

OBJ_C		= $(SRC_C:.c=.o)

CC		= gcc

RM		= rm -f

CFLAGS		+= -W -Wall -Wextra -I./includes -D_GNU_SOURCE -g3

all:		$(NAME_S) $(NAME_C)

$(NAME_S):	$(OBJ_S)
		$(CC) -o $(NAME_S) $(OBJ_S)

$(NAME_C):	$(OBJ_C)
		$(CC) -o $(NAME_C) $(OBJ_C) -pthread -L./GraphApp_3.64 -lapp

clean:
		$(RM) $(OBJ_S) $(OBJ_C)

fclean:		clean
		rm -f $(NAME_S) $(NAME_C)

re:		fclean all

.PHONY:		all clean fclean re
