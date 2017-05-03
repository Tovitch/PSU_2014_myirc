/*
** cmd_server.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Apr  3 10:47:34 2015 Tony Kruszkewycz
** Last update Wed Jul  8 12:25:34 2015 Tony Kruszkewycz
*/

#include		<sys/types.h>  /* socket/connect */
#include		<sys/socket.h> /* socket/connect */
#include		<netdb.h> /* getaddrinfo */
#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<string.h>
#include		<pthread.h>
#include		"client.h"

static int		check_format(char *str)
{
  int			i;

  for (i = 0; str[i]; ++i)
    {
      if (str[i] == ':')
	return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}

static void		init_hints(struct addrinfo *hints)
{
  memset(hints, 0, sizeof(*hints));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
}

static int		srv_connect(char *host, char *port)
{
  struct addrinfo	hints;
  struct addrinfo	*servinfo;
  int			status;
  int			sfd;

  init_hints(&hints);
  if ((status = getaddrinfo(host, port, &hints, &servinfo)) != 0)
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
      return (EXIT_FAILURE);
    }
  if ((sfd = socket(servinfo->ai_family, servinfo->ai_socktype,
		    servinfo->ai_protocol)) == -1)
    {
      perror("socket");
      return (EXIT_FAILURE);
    }
  if ((connect(sfd, servinfo->ai_addr, servinfo->ai_addrlen)) == -1)
    {
      close(sfd);
      perror("connect");
      return (EXIT_FAILURE);
    }
  freeaddrinfo(servinfo);
  return (sfd);
}

void			*rdMsg(void *data)
{
  t_env			*e;
  int			r;
  char			msg[MAX_MSG + 1];

  e = (t_env *)data;
  while (1)
    {
      memset(msg, 0, sizeof(msg));
      if ((r = recv(e->sfd, msg, sizeof(msg), 0)) > 0)
      	{
      	  if (strcmp(msg, "ok") == 0)
	    e->state = 1;
	  else if ((strcmp(msg, NICK_ARD_USED)) == 0)
	    {
	      e->state = 2;
	      write(2, msg, r);
	    }
	  else
	    write(1, msg, r);
      	}
    }
}

int			cmd_server(t_env *e, char **entry)
{
  pthread_t		th;
  char			*port;
  char			buf[WELCOME_SZ];
  int			r;

  if (!entry[1] || check_format(entry[1]) == EXIT_FAILURE)
    return (SRV_FMT);
  port = strstr(entry[1], ":") + 1;
  entry[1][strlen(entry[1]) - strlen(port) - 1] = 0;
  if ((e->sfd = srv_connect(entry[1], port)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if ((write(e->sfd, e->nickname, strlen(e->nickname))) == -1)
    return (EXIT_FAILURE);
  memset(buf, 0, WELCOME_SZ);
  if ((r = read(e->sfd, buf, WELCOME_SZ)) == -1)
    return (EXIT_FAILURE);
  write(1, buf, r);
  if ((strcmp(buf, NICK_ARD_USED)) == 0)
    {
      close(e->sfd);
      e->sfd = NOT_LOGGED;
      return (EXIT_SUCCESS);
    }
  if ((pthread_create(&th, NULL, rdMsg, e)) != 0)
    perror("run_clt>pthread_create");
  return (EXIT_SUCCESS);
}
