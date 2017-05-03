/*
** cmd_list.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 16:10:13 2015 kruszk_t
** Last update Wed Apr 15 16:21:21 2015 kruszk_t
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<string.h>
#include		<stdio.h>
#include		"client.h"

int			cmd_list(t_env *e, char **entry)
{
  char			*tmp;
  int			size;

  if (e->sfd == NOT_LOGGED)
    return (NOT_LOG_SRV);
  for (size = 0; entry[size]; ++size);
  if (size == 1)
    write(e->sfd, entry[0], strlen(entry[0]) + 1);
  else
    {
      size = strlen(entry[0]) + strlen(entry[1]);
      if (!(tmp = malloc(sizeof(char) * size + 1)))
	return (EXIT_FAILURE);
      sprintf(tmp, "%s %s", entry[0], entry[1]);
      write(e->sfd, tmp, strlen(tmp) + 1);
      free(tmp);
    }
  return (EXIT_SUCCESS);
}
