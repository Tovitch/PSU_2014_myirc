/*
** cmd_users.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 16:18:35 2015 kruszk_t
** Last update Wed Apr 15 16:19:08 2015 kruszk_t
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<string.h>
#include		"client.h"

int			cmd_users(t_env *e, char **entry)
{
  if (e->sfd == NOT_LOGGED)
    return (NOT_LOG_SRV);
  if (e->chan == NULL)
    return (EMPTY_CHAN_LIST);
  write(e->sfd, entry[0], strlen(entry[0]) + 1);
  return (EXIT_SUCCESS);
}
