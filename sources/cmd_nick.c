/*
** cmd_nick.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 16:07:18 2015 kruszk_t
** Last update Wed Jul  8 12:31:07 2015 Tony Kruszkewycz
*/

#include		<stdlib.h>
#include		<string.h>
#include		<stdio.h>
#include		<unistd.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		"client.h"

static int		check_forbidden_char(char *msg)
{
  int			i;

  if (!msg)
    return (EXIT_FAILURE);
  for (i = 0; msg[i]; ++i)
    {
      if ((msg[i] >= 6 && msg[i] <= 47) || (msg[i] >= 58 && msg[i] <= 64) ||
	  (msg[i] >= 91 && msg[i] <= 96) || msg[i] >= 123)
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static int		change_nick(t_env *e, char **entry, int ret)
{
  memset(e->nickname, 0, MAX_NICK);
  strcpy(e->nickname, entry[1]);
  return (ret);
}

int			cmd_nick(t_env *e, char **entry)
{
  char			*tmp;

  if (!entry[1])
    {
      puts("Veuillez spécifier un pseudonyme (/nick [NICKNAME])");
      return (EXIT_SUCCESS);
    }
  if (check_forbidden_char(entry[1]) == EXIT_FAILURE)
    {
      puts("Ce pseudonyme contient des caractères interdis");
      puts("Veuillez en choisir un autre");
      return (EXIT_FAILURE);
    }
  if (e->sfd == NOT_LOGGED)
    return (change_nick(e, entry, EXIT_SUCCESS));
  if (!(tmp = malloc(sizeof(char) * strlen(entry[0]) + strlen(entry[1]) + 2)))
    return (EXIT_FAILURE);
  sprintf(tmp, "%s %s", entry[0], entry[1]);
  write(e->sfd, tmp, strlen(tmp) + 1);
  free(tmp);
  usleep(500000);
  if (e->state == 2)
    return (EXIT_SUCCESS);
  return (change_nick(e, entry, EXIT_SUCCESS));
}
