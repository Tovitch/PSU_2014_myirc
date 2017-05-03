/*
** send_msg.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 12:37:23 2015 kruszk_t
** Last update Wed Apr 15 12:38:45 2015 kruszk_t
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<string.h>
#include		<stdio.h>
#include		"server.h"

void			send_msg(t_env *e, int fd, char *cmd)
{
  char			**tab;
  char			msg[MAX_NICK + MAX_MSG + 10];
  int			i;

  if (!(tab = my_str_to_wordtab(cmd)))
    return ;
  if ((check_nick_by_channel(e, fd, tab[1])) == EXIT_FAILURE)
    {
      write(fd, USER_NOT_FOUND_MSG, strlen(USER_NOT_FOUND_MSG) + 1);
      return ;
    }
  memset(msg, 0, sizeof(msg));
  sprintf(msg, "msg de %s:", e->nickname[fd]);
  for (i = 2; tab[i]; ++i)
    sprintf(msg, "%s %s", msg, tab[i]);
  for (i = 0; i < MAX_FD; ++i)
    {
      if (e->fd_type[i] == FD_CLIENT && strcmp(tab[1], e->nickname[i]) == 0)
	write(i, msg, strlen(msg) + 1);
    }
  write(fd, "ok", strlen("ok") + 1);
  delete_tab(tab);
}
