/*
** send_list.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 12:25:06 2015 kruszk_t
** Last update Wed Jul  8 13:27:54 2015 Tony Kruszkewycz
*/

#include		<string.h>
#include		<stdio.h>
#include		<unistd.h>
#include		"server.h"

static void		with_arg(t_env *e, int cfd, char *arg)
{
  char			tmp[MAX_CHANNEL + 2];
  t_chan		*chan;

  chan = e->chan;
  while (chan)
    {
      if (strcasestr(chan->_chan, arg) != NULL)
	{
	  memset(tmp, 0, sizeof(tmp));
	  sprintf(tmp, "%s\n", chan->_chan);
	  write(cfd, tmp, strlen(tmp));
	}
      chan = chan->next;
    }
}

static void		without_arg(t_env *e, int cfd)
{
  char			tmp[MAX_CHANNEL + 2];
  t_chan		*chan;

  chan = e->chan;
  while (chan)
    {
      memset(tmp, 0, sizeof(tmp));
      sprintf(tmp, "%s\n", chan->_chan);
      write(cfd, tmp, strlen(tmp));
      chan = chan->next;
    }
}

void			send_list(t_env *e, int cfd, char *cmd)
{
  char			**tab;

  if (!(tab = my_str_to_wordtab(cmd)))
    return ;
  if (tab[1] == NULL)
    without_arg(e, cfd);
  else
    with_arg(e, cfd, tab[1]);
  delete_tab(tab);
}
