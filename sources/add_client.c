/*
** add_client.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Mar 30 17:54:40 2015 Tony Kruszkewycz
** Last update Wed Jul  8 13:23:29 2015 Tony Kruszkewycz
*/

#include		<string.h>
#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		"server.h"

int			check_nick(t_env *e, char *nick)
{
  int			i;

  for (i = 0; i < MAX_FD; ++i)
    {
      if (e->fd_type[i] == FD_CLIENT && strcmp(e->nickname[i], nick) == 0)
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static int		get_nick(t_env *e, int cs)
{
 char			nick[MAX_NICK];
 int			ret;

  memset(nick, 0, sizeof(nick));
  memset(e->nickname[cs], 0, sizeof(e->nickname[cs]));
  if ((ret = read(cs, nick, MAX_NICK)) == -1)
    return (EXIT_FAILURE);
  nick[ret] = 0;
  if (check_nick(e, nick) == EXIT_FAILURE)
    {
      write(cs, NICK_ARD_USED, strlen(NICK_ARD_USED));
      close(cs);
      return (EXIT_FAILURE);
    }
  strcpy(e->nickname[cs], nick);
  return (EXIT_SUCCESS);
}

int			add_client(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	clt_sin;
  socklen_t		clt_sin_len;
  char			welcome[WELCOME_SZ];

  clt_sin_len = sizeof(clt_sin);
  if ((cs = accept(s, (struct sockaddr *)&clt_sin, &clt_sin_len)) == -1)
    {
      perror("accept");
      return (EXIT_FAILURE);
    }
  if ((get_nick(e, cs)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  e->fd_type[cs] = FD_CLIENT;
  e->ft_read[cs] = client_read;
  e->ft_write[cs] = client_write;
  e->user_chan[cs] = NULL;
  printf("%s:%d: connecté !\n", e->nickname[cs], cs);
  memset(welcome, 0, WELCOME_SZ);
  sprintf(welcome, WELCOME_MSG" %s !\n", e->nickname[cs]);
  write(cs, welcome, strlen(welcome));
  return (EXIT_SUCCESS);
}
