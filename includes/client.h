/*
** client.h for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr  1 11:15:02 2015 kruszk_t
** Last update Wed Jul  8 11:51:52 2015 Tony Kruszkewycz
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# define		MAX_FD 255
# define		BUF_SZ 4096
# define		MAX_MSG 80
# define		MAX_NICK 18
# define		WELCOME_SZ 12 + MAX_NICK
# define		MAX_CMD 9
# define		MAX_CMD_SZ 12
# define		MAX_PORT 5
# define		MAX_ERR 14
# define		MAX_ERR_MSG 55
# define		MAX_CHANNEL 20
# define		NOT_LOGGED -1

# define		NICK_ARD_USED "Ce pseudo est déjà utilisé\n"
# define		EXIT_FAILURE_MSG "Une erreur est survenue\n"
# define		SRV_FMT_MSG "Mauvaise syntaxe (/server HOST:PORT)\n"
# define		NOT_LOGGED_MSG "Vous n'êtes pas connecté a un serveur\n"
# define		NOT_LOGGED_CHAN "Vous n'êtes pas connecté a un canal de discussion\n"
# define		UNKNOWN_CHAN_MSG "Canal introuvable\n"
# define		NOT_IN_CHAN_MSG "Vous n'êtes pas dans ce canal\n"
# define		CHAN_ARD_ADD_MSG "Vous avez déjà joint ce canal\n"
# define		EMPTY_CHAN_LIST_MSG "Vous n'avez pas joint ce canal\n"
# define		UNKNOWN_CMD_MSG "%s: commande inconnue\n"
# define		MSG_USAGE_MSG "Mauvaise syntaxe (/msg NICKNAME MESSAGE\n"
# define		MSG_SUCCESS "Message envoyé avec succès"
# define		MSG_FAILED_MSG "Le message n'a pas été envoyé\n"
# define		USER_NOT_FOUND_MSG "Aucun utilisateur de ce nom\n"
# define		SEND_FILE_USAGE_MSG "Maivaise syntaxe (/send_file NICKNAME MESSAGE)\n"
# define		SEND_FILE_FAILED_MSG "Envoi du fichier échoué\n"
# define		ACCEPT_FILE_USAGE_MSG "Maivaise syntaxe (/accept_file NICKNAME)\n"
# define		ACCEPT_FILE_FAILED_MSG "/accept_file échoué\n"
# define		BAD_FILE_MSG "Mauvais format de fichier\n"

# define		str(x) # x
# define		xstr(x) str(x)

enum
  { SRV_FMT = 12,
    NOT_LOG_SRV,
    NOT_LOG_CHAN,
    UNKNOWN_CHAN,
    NOT_IN_CHAN,
    CHAN_ARD_ADD,
    EMPTY_CHAN_LIST,
    UNKNOWN_CMD,
    MSG_USAGE,
    MSG_FAILED,
    SEND_FILE_USAGE,
    SEND_FILE_FAILED,
    ACCEPT_FILE_USAGE,
    ACCEPT_FILE_FAILED,
    BAD_FILE};

typedef int(*ft)();

typedef struct		s_cmd
{
  char			name[MAX_CMD_SZ];
  ft			cmd;
}			t_cmd;

typedef struct		s_chan
{
  char			_chan[MAX_CHANNEL];
  char			users[MAX_FD][MAX_NICK];
  struct s_chan		*next;
}			t_chan;

typedef struct		s_env
{
  int			sfd;
  char			nickname[MAX_NICK];
  int			state;
  char			err[MAX_ERR][MAX_ERR_MSG];
  char			*host;
  t_chan		*chan;
  struct s_cmd		cmds[MAX_CMD];
}			t_env;

int			cmd_server(t_env *, char **);
int			cmd_nick(t_env *, char **);
int			cmd_list(t_env *, char **);
int			cmd_join(t_env *, char **);
int			cmd_part(t_env *, char **);
int			cmd_users(t_env *, char **);
int			cmd_msg(t_env *, char **);
int			cmd_sendFile(t_env *, char **);
int			cmd_acceptFile(t_env *, char **);

int			run_clt(t_env *);
void			check_ret(t_env *, int);

int			add_chan(t_chan **, char *);
int			rm_chan(t_chan **, char *);

char			**my_str_to_wordtab(char *);
void			delete_tab(char **);
char			*my_strdup(char *);

#endif /* !CLIENT_H_ */
