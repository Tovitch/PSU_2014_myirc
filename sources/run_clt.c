/*
** run_clt.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 14:03:30 2015 kruszk_t
** Last update Wed Jul  8 15:38:14 2015 Tony Kruszkewycz
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<string.h>
#include		<stdio.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		"client.h"

static void		print_prompt(t_env *e)
{
  write(1, e->nickname, strlen(e->nickname));
  write(1, ": ", 2);
}

static void		check_cmd(t_env *e, char **entry)
{
  int			i;
  int			ret;

  ret = UNKNOWN_CMD;
  for (i = 0; i < MAX_CMD; ++i)
    {
      if (strcmp(entry[0], e->cmds[i].name) == 0)
	{
	  ret = e->cmds[i].cmd(e, entry);
	  check_ret(e, ret);
	}
    }
  if (ret == UNKNOWN_CMD)
    fprintf(stderr, UNKNOWN_CMD_MSG, entry[0]);
}

static void		send_msg(t_env *e, char *msg)
{
  if (e->sfd != NOT_LOGGED && e->chan != NULL)
    send(e->sfd, msg, strlen(msg) + 1, 0);
  else
    check_ret(e, (e->sfd == NOT_LOGGED) ? NOT_LOG_SRV : NOT_LOG_CHAN);
}

int			run_clt(t_env *e)
{
  char			*msg;
  size_t		lmsg;
  size_t		alloc_size;
  char			**tab;

  msg = NULL;
  alloc_size = 0;
  while (42)
    {
      if (e->chan == NULL)
	print_prompt(e);
      if ((lmsg = getline(&msg, &alloc_size, stdin)) > 0)
	{
	  (lmsg) ? (msg[lmsg - 1] = 0) : (msg[lmsg] = 0);
	  tab = NULL;
	  if ((tab = my_str_to_wordtab(msg)))
	    {
	      (tab[0][0] == '/') ? check_cmd(e, tab) : send_msg(e, msg);
	      delete_tab(tab);
	    }
	}
    }
  if (alloc_size)
    free(msg);
  return (EXIT_SUCCESS);
}
