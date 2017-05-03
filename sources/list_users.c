/*
** list_users.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 12:39:17 2015 kruszk_t
** Last update Wed Apr 15 12:39:50 2015 kruszk_t
*/

#include		<stdio.h>
#include		<string.h>
#include		<unistd.h>
#include		"server.h"

void			list_users(t_env *e, int cfd)
{
  char			tmp[BUF_SZ + 1];
  int			i;

  memset(tmp, 0, sizeof(tmp));
  for (i = 0; i < MAX_FD; ++i)
    {
      if (e->fd_type[i] == FD_CLIENT &&
	  strcmp(e->user_chan[cfd]->_chan, e->user_chan[i]->_chan) == 0)
	{
	  if (!tmp[0])
	    sprintf(tmp, "%s\n", e->nickname[i]);
	  else
	    sprintf(tmp, "%s%s\n", tmp, e->nickname[i]);
	}
    }
  write(cfd, tmp, strlen(tmp) + 1);
}
