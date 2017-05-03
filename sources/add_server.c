/*
** add_server.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Mar 30 10:12:09 2015 Tony Kruszkewycz
** Last update Wed Jul  8 15:45:35 2015 Tony Kruszkewycz
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<string.h>
#include		"server.h"

int			server_read(t_env *e, int fd)
{
  write(1, "Tentative de connexion...\n", 27);
  if ((add_client(e, fd)) == EXIT_FAILURE)
    write(1, "Déconnecté...\n", 16);
  return (EXIT_SUCCESS);
}

static t_chan		*init_chan()
{
  static char		*channel[] = {"ADA", "BASIC", "C", "C++", "Cobol",
				      "Fortran", "Java", "MATLAB",
				      "Mathematica", "LISP", "Pascal", "PHP",
				      "Prolog", "Perl"};
  t_chan		*chan;
  int			i;

  chan = NULL;
  for (i = 0; i < NB_CHAN; ++i)
    add_chan(&chan, channel[i]);
  return (chan);
}

static void		server_info(t_env *e, int s)
{
  e->fd_type[s] = FD_SERVER;
  e->ft_read[s] = server_read;
  e->ft_write[s] = NULL;
  e->chan = init_chan();
}

static struct addrinfo	*fill_hints(struct addrinfo *hints, int *s, t_env *e)
{
  struct addrinfo	*srvi;

  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  e->cltAddrLen = sizeof(e->cltAddr);
  if ((*s = getaddrinfo(NULL, e->listenPort, hints, &srvi)) != 0)
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(*s));
      return (NULL);
    }
  if ((*s = socket(srvi->ai_family, srvi->ai_socktype, srvi->ai_protocol)) < 0)
    {
      perror("socket");
      return (NULL);
    }
  return (srvi);
}

int			add_server(t_env *e)
{
  struct addrinfo	hints;
  struct addrinfo	*srvi;
  int			s;

  if ((srvi = fill_hints(&hints, &s, e)) == NULL)
    return (EXIT_FAILURE);
  if ((bind(s, srvi->ai_addr, srvi->ai_addrlen)) == -1)
    {
      perror("bind");
      return (EXIT_FAILURE);
    }
  if ((listen(s, MAX_FD)) == -1)
    {
      perror("listen");
      return (EXIT_FAILURE);
    }
  freeaddrinfo(srvi);
  server_info(e, s);
  return (EXIT_SUCCESS);
}
