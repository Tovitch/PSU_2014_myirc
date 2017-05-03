/*
** server.h for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Mar 27 12:00:05 2015 kruszk_t
** Last update Wed Jul  8 11:40:27 2015 Tony Kruszkewycz
*/

#ifndef SERVER_H_
# define SERVER_H_

# include		<sys/types.h>
# include		<sys/socket.h>
# include		<netdb.h>

# define		WELCOME_MSG "Bienvenue"
# define		NICK_ARD_USED "Ce pseudo est déjà utilisé\n"
# define		UNKNOWN_CHAN_MSG "Canal introuvable\n"
# define		USER_NOT_FOUND_MSG "Aucun utilisateur de ce nom\n"
# define		CHK_NICK_CHAN_MSG "check_nick_by_channel() failed\n"

# define		MAX_MSG 80
# define		MAX_FD 255
# define		MAX_NICK 18
# define		WELCOME_SZ 12 + MAX_NICK
# define		MAX_CHANNEL 20
# define		NB_CHAN 14
# define		MAX_CMD 7
# define		BUF_SZ 4096
# define		JOIN 0
# define		PART 1

enum
  { FD_FREE, FD_CLIENT, FD_SERVER };

typedef int(*ft)();

typedef struct		s_chan
{
  char			_chan[MAX_CHANNEL];
  char			users[MAX_FD][MAX_NICK];
  struct s_chan		*next;
}			t_chan;

typedef struct		s_env
{
  char			*listenPort;
  char			nickname[MAX_FD][MAX_NICK];
  t_chan		*user_chan[MAX_FD];
  t_chan		*chan;
  char			fd_type[MAX_FD];
  ft			ft_read[MAX_FD];
  ft			ft_write[MAX_FD];
  struct sockaddr_in	cltAddr;
  int			cltAddrLen;
}			t_env;

int			add_server(t_env *);
int			add_client(t_env *, int);
int			add_chan(t_chan **, char *);
int			rm_chan(t_chan **, char *);
void			add_user_to_chan(t_chan **, char *, int, char *);
void			rm_user_to_chan(t_chan **, char *, int);
char			**my_str_to_wordtab(char *);
void			delete_tab(char **);
int			check_nick_by_channel(t_env *, int, char *);
int			check_nick(t_env *e, char *nick);

int			client_write(t_env *, char *, int, int);
int			client_read(t_env *, int);

void			send_list(t_env *, int, char *);
void			send_file(t_env *e, int fd, char *cmd);
void			accept_file(t_env *e, int fd, char *cmd);
void			send_msg(t_env *, int, char *);
void			list_users(t_env *, int);
void			joinPart_chan(t_env *, int, char *, int);

#endif /* !SERVER_H_ */
