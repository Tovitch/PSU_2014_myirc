/*
** read_client.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 12:00:01 2015 kruszk_t
** Last update Wed Jul  8 16:53:00 2015 Tony Kruszkewycz
*/

#include		<stdlib.h>
#include		<string.h>
#include		<unistd.h>
#include		<stdio.h>
#include		"server.h"

int			check_nick_by_channel(t_env *e, int fd, char *nick)
{
  t_chan		*check;
  int			i;

  check = e->chan;
  while (check)
    {
      for (i = 0; i < MAX_FD; ++i)
	{
	  if (e->fd_type[i] == FD_CLIENT &&
	      (strcmp(check->users[i], nick) == 0 && check->users[fd][0] != 0))
	    return (i);
	}
      check = check->next;
    }
  return (EXIT_FAILURE);
}

static void		msg(t_env *e, int fd, char *buf)
{
  int			i;

  for (i = 0; i < MAX_FD; ++i)
    {
      if (e->fd_type[i] == FD_CLIENT &&
	  e->user_chan[fd]->_chan &&
	  strcmp(e->user_chan[fd]->_chan, e->user_chan[i]->_chan) == 0)
	e->ft_write[i](e, buf, fd, i);
    }
}

static int		set_nick(t_env *e, int fd, char *buf)
{
  char			**tab;

  if (!(tab = my_str_to_wordtab(buf)))
    return (EXIT_FAILURE);
  if (check_nick(e, tab[1]) == EXIT_FAILURE)
    {
      write(fd, NICK_ARD_USED, strlen(NICK_ARD_USED));
      return (EXIT_FAILURE);
    }
  bzero(e->nickname[fd], sizeof(e->nickname[fd]));
  strcpy(e->nickname[fd], tab[1]);
  delete_tab(tab);
  return (EXIT_SUCCESS);
}

static void		exec_cmd(t_env *e, int fd, char *buf)
{
  if (strncmp(buf, "/list", strlen("/list")) == 0)
    send_list(e, fd, buf);
  else if (strncmp(buf, "/join", strlen("/join")) == 0)
    joinPart_chan(e, fd, buf, JOIN);
  else if (strncmp(buf, "/part", strlen("/part")) == 0)
    joinPart_chan(e, fd, buf, PART);
  else if (strncmp(buf, "/users", strlen("/users")) == 0)
    list_users(e, fd);
  else if (strncmp(buf, "/msg", strlen("/msg")) == 0)
    send_msg(e, fd, buf);
  else if (strncmp(buf, "/send_file", strlen("/send_file")) == 0)
    send_file(e, fd, buf);
  else if (strncmp(buf, "/accept_file", strlen("/accept_file")) == 0)
    accept_file(e, fd, buf);
  else if (strncmp(buf, "/nick", strlen("/nick")) == 0)
    set_nick(e, fd, buf);
}

int			client_read(t_env *e, int fd)
{
  int			r;
  char			buf[BUF_SZ];

  memset(buf, 0, sizeof(buf));
  r = read(fd, buf, BUF_SZ);
  if (r > 0)
    {
      buf[r - 1] = 0;
      printf("%s: %s\n", e->nickname[fd], buf);
      if (buf[0] != '/')
	msg(e, fd, buf);
      else
	exec_cmd(e, fd, buf);
    }
  else
    {
      printf("%d: Connexion terminée\n", fd);
      close(fd);
      e->fd_type[fd] = FD_FREE;
    }
  return (EXIT_SUCCESS);
}
