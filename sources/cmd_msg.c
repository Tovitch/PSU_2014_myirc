/*
** cmd_msg.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 16:19:43 2015 kruszk_t
** Last update Wed Jul  8 13:46:47 2015 Tony Kruszkewycz
*/

#include		<stdlib.h>
#include		<string.h>
#include		<unistd.h>
#include		<stdio.h>
#include		"client.h"

int			cmd_msg(t_env *e, char **entry)
{
  char			tmp[MAX_NICK + MAX_MSG + 7];
  int			i;

  if (e->sfd == NOT_LOGGED)
    return (NOT_LOG_SRV);
  if (e->chan == NULL)
    return (EMPTY_CHAN_LIST);
  if (entry[1] == NULL || entry[2] == NULL)
    return (MSG_USAGE);
  memset(tmp, 0, sizeof(tmp));
  sprintf(tmp, "%s %s", entry[0], entry[1]);
  for (i = 2; entry[i]; ++i)
    sprintf(tmp, "%s %s", tmp, entry[i]);
  sprintf(tmp, "%s\n", tmp);
  write(e->sfd, tmp, strlen(tmp) + 1);
  write(1, "Envoi en cours...\n", strlen("Envoi en cours...\n"));
  usleep(500000);
  if (e->state == 0)
    {
      write(2, MSG_FAILED_MSG, strlen(MSG_FAILED_MSG));
      return (MSG_FAILED);
    }
  e->state = 0;
  puts(MSG_SUCCESS);
  return (EXIT_SUCCESS);
}
