/*
** main_server.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Thu Mar 26 17:48:23 2015 kruszk_t
** Last update Wed Jul  8 15:27:06 2015 Tony Kruszkewycz
*/

#include		<stdlib.h>
#include		<string.h>
#include		<stdio.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netdb.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		<unistd.h>
#include		"server.h"

int			serv_listen(t_env *e)
{
  fd_set		rfd;
  int			fd_max;
  int			i;

  while (1)
    {
      FD_ZERO(&rfd);
      fd_max = 0;
      for (i = 0; i < MAX_FD; ++i)
	{
	  if (e->fd_type[i] != FD_FREE)
	    {
	      FD_SET(i, &rfd);
	      fd_max = i;
	    }
	}
      if (select(fd_max + 1, &rfd, NULL, NULL, NULL) == -1)
	perror("select");
      for (i = 0; i < MAX_FD; ++i)
	{
	  if (FD_ISSET(i, &rfd))
	    e->ft_read[i](e, i);
	}
    }
  return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
  t_env			e;

  memset(e.fd_type, FD_FREE, MAX_FD);
  (ac < 2) ? (e.listenPort = "4242") : (e.listenPort = av[1]);
  if (add_server(&e) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  printf("Attente de connexion TCP sur le port %s\n", e.listenPort);
  if (serv_listen(&e) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
