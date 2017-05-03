/*
** send_accept_file.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 12:34:34 2015 kruszk_t
** Last update Wed Apr 15 12:37:06 2015 kruszk_t
*/

#include		<unistd.h>
#include		<stdlib.h>
#include		<string.h>
#include		"server.h"

void			send_file(t_env *e, int fd, char *cmd)
{
  char			**tab;
  int			recvfd;

  if (!(tab = my_str_to_wordtab(cmd)))
    return ;
  if ((recvfd = check_nick_by_channel(e, fd, tab[1])) == EXIT_FAILURE)
    {
      write(fd, USER_NOT_FOUND_MSG, strlen(USER_NOT_FOUND_MSG) + 1);
      return ;
    }
  delete_tab(tab);
}

void			accept_file(t_env *e, int fd, char *cmd)
{
  (void)e;
  (void)fd;
  (void)cmd;
}
