/*
** join_part_chan.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 12:40:40 2015 kruszk_t
** Last update Wed Jul  8 13:31:17 2015 Tony Kruszkewycz
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<string.h>
#include		"server.h"

static int		chan_cmp(t_chan *chan, char *to_cmp)
{
  t_chan		*tmp;

  tmp = chan;
  while (tmp)
    {
      if (strcmp(tmp->_chan, to_cmp) == 0)
	return (EXIT_SUCCESS);
      tmp = tmp->next;
    }
  return (EXIT_FAILURE);
}

void			joinPart_chan(t_env *e, int cfd, char *cmd, int state)
{
  char			**tab;

  if (!(tab = my_str_to_wordtab(cmd)))
    return ;
  if (chan_cmp(e->chan, tab[1]) == EXIT_FAILURE)
    {
      write(cfd, UNKNOWN_CHAN_MSG, strlen(UNKNOWN_CHAN_MSG) + 1);
      return ;
    }
  if (state == JOIN)
    {
      add_chan(&e->user_chan[cfd], tab[1]);
      add_user_to_chan(&e->chan, tab[1], cfd, e->nickname[cfd]);
    }
  else
    {
      rm_chan(&e->user_chan[cfd], tab[1]);
      rm_user_to_chan(&e->chan, tab[1], cfd);
    }
  write(cfd, "ok", strlen("ok") + 1);
}
