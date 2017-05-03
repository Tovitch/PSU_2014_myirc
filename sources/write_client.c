/*
** write_client.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 12:00:29 2015 kruszk_t
** Last update Wed Jul  8 15:42:22 2015 Tony Kruszkewycz
*/

#include		<stdlib.h>
#include		<string.h>
#include		<unistd.h>
#include		<stdio.h>
#include		"server.h"

int			client_write(t_env *e, char *str, int sender,
				     int reciver)
{
  char			*tmp;

  if (!(tmp = malloc(sizeof(char) * (strlen(e->nickname[sender])
				     + strlen(str) + 4))))
    return (EXIT_FAILURE);
  sprintf(tmp, "%s: %s\n", e->nickname[sender], str);
  write(reciver, tmp, strlen(tmp) + 1);
  free(tmp);
  return (EXIT_SUCCESS);
}
