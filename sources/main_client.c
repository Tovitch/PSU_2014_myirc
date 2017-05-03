/*
** main_client.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Thu Mar 26 17:48:55 2015 kruszk_t
** Last update Wed Apr 15 16:05:57 2015 kruszk_t
*/

#include		<pthread.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<strings.h>
#include		<string.h>
#include		<unistd.h>
#include		"client.h"

void			init_env(t_env *e)
{
  static char		*cName[] = {"/server", "/nick", "/list", "/join",
				    "/part", "/users", "/msg", "/send_file",
				    "/accept_file"};
  static ft		cFt[] = {cmd_server, cmd_nick, cmd_list, cmd_join,
				 cmd_part, cmd_users, cmd_msg, cmd_sendFile,
				 cmd_acceptFile};
  int			i;

  for (i = 0; i < MAX_CMD; ++i)
    {
      bzero(e->cmds[i].name, sizeof(e->cmds[i].name));
      strcpy(e->cmds[i].name, cName[i]);
      e->cmds[i].cmd = cFt[i];
    }
  memset(e->nickname, 0, sizeof(e->nickname));
  strcpy(e->nickname, "Anonymous");
  e->sfd = NOT_LOGGED;
  e->chan = NULL;
  e->state = 0;
}

void			check_ret(t_env *e, int ret)
{
  write(2, e->err[ret -11], strlen(e->err[ret -11]));
}

static void		init_check_ret(t_env *e)
{
  static char		*err[] = {EXIT_FAILURE_MSG, SRV_FMT_MSG,
				  NOT_LOGGED_MSG, NOT_LOGGED_CHAN,
				  UNKNOWN_CHAN_MSG, NOT_IN_CHAN_MSG,
				  CHAN_ARD_ADD_MSG, EMPTY_CHAN_LIST_MSG,
				  USER_NOT_FOUND_MSG, SEND_FILE_USAGE_MSG,
				  SEND_FILE_FAILED_MSG, ACCEPT_FILE_USAGE_MSG,
				  ACCEPT_FILE_FAILED_MSG, BAD_FILE_MSG};
  int			i;

  for (i = 0; i < MAX_ERR; ++i)
    {
      memset(e->err[i], 0, sizeof(e->err[i]));
      strcpy(e->err[i], err[i]);
    }
}

int			main()
{
  t_env			e;

  init_env(&e);
  init_check_ret(&e);
  if ((run_clt(&e)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
