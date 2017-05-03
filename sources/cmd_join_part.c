/*
** cmd_join_part.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 16:11:07 2015 kruszk_t
** Last update Wed Jul  8 13:44:22 2015 Tony Kruszkewycz
*/

#include		<stdlib.h>
#include		<stdio.h>
#include		<string.h>
#include		<unistd.h>
#include		"client.h"

static int		check_login(t_env *e, char **entry, int state)
{
  if (state == 0)
    {
      if (e->sfd == NOT_LOGGED)
	return (NOT_LOG_SRV);
      if (!entry[1])
	return (UNKNOWN_CHAN);
    }
  else
    {
      if (e->sfd == NOT_LOGGED)
	return (NOT_LOG_SRV);
      if (e->chan == NULL)
	return (NOT_LOG_CHAN);
      if (!entry[1])
	return (UNKNOWN_CHAN);
    }
  return (EXIT_SUCCESS);
}

int			cmd_join(t_env *e, char **entry)
{
  char			*tmp;
  int			size;

  if ((size = check_login(e, entry, 0)) != EXIT_SUCCESS)
    return (size);
  size = strlen(entry[0]) + strlen(entry[1]);
  if (!(tmp = malloc(sizeof(char) * size + 1)))
    return (EXIT_FAILURE);
  sprintf(tmp, "%s %s", entry[0], entry[1]);
  write(e->sfd, tmp, strlen(tmp) + 1);
  usleep(500000);
  free(tmp);
  if (e->state == 1)
    {
      e->state = 0;
      if ((add_chan(&e->chan, entry[1])) == CHAN_ARD_ADD)
	return (CHAN_ARD_ADD);
    }
  else
    return (EXIT_FAILURE);
  printf("Vous avez rejoint %s\n", entry[1]);
  return (EXIT_SUCCESS);
}

int			cmd_part(t_env *e, char **entry)
{
  char			*tmp;
  int			size;

  if ((size = check_login(e, entry, 1)) != EXIT_SUCCESS)
    return (size);
  size = strlen(entry[0]) + strlen(entry[1]);
  if (!(tmp = malloc(sizeof(char) * size + 1)))
    return (EXIT_FAILURE);
  sprintf(tmp, "%s %s", entry[0], entry[1]);
  write(e->sfd, tmp, strlen(tmp) + 1);
  usleep(500000);
  free(tmp);
  if (e->state == 1)
    {
      e->state = 0;
      if ((rm_chan(&e->chan, entry[1])) == EMPTY_CHAN_LIST)
	return (EMPTY_CHAN_LIST);
    }
  else
    return (EXIT_FAILURE);
  printf("Vous avez quitté %s\n", entry[1]);
  return (EXIT_SUCCESS);
}
