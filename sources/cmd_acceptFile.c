/*
** cmd_acceptFile.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 16:24:35 2015 kruszk_t
** Last update Wed Jul  8 13:47:12 2015 Tony Kruszkewycz
*/

#include		<stdlib.h>
#include		<string.h>
#include		<stdio.h>
#include		<unistd.h>
#include		"client.h"

int			cmd_acceptFile(t_env *e, char **entry)
{
  char			tmp[MAX_NICK + MAX_MSG + 12];

  if (e->sfd == NOT_LOGGED)
    return (NOT_LOG_SRV);
  if (e->chan == NULL)
    return (EMPTY_CHAN_LIST);
  if (entry[1] == NULL)
    return (ACCEPT_FILE_USAGE);
  memset(tmp, 0, sizeof(tmp));
  sprintf(tmp, "%s %s", entry[0], entry[1]);
  write(e->sfd, tmp, strlen(tmp) + 1);
  usleep(500000);
  if (e->state == 0)
    {
      write(2, ACCEPT_FILE_FAILED_MSG, strlen(ACCEPT_FILE_FAILED_MSG));
      return (ACCEPT_FILE_FAILED);
    }
  e->state = 0;
  return (EXIT_SUCCESS);
}
