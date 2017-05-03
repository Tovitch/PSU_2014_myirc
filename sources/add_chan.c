/*
** add_chan.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr  8 14:31:57 2015 Tony Kruszkewycz
** Last update Fri Apr 10 17:53:17 2015 kruszk_t
*/

#include	<stdlib.h>
#include	<string.h>
#include	"client.h"

int		add_chan(t_chan **chan, char *chan_name)
{
  t_chan		*tmp;
  t_chan		*new;

  if (!(new = malloc(sizeof(t_chan))))
    return (EXIT_FAILURE);
  memset(new->_chan, 0, MAX_CHANNEL);
  strcpy(new->_chan, chan_name);
  new->next = NULL;
  if (*chan == NULL)
    *chan = new;
  else
    {
      tmp = *chan;
      while (tmp->next)
	{
	  if (strcmp(tmp->_chan, chan_name) == 0)
	    return (CHAN_ARD_ADD);
	  tmp = tmp->next;
	}
      tmp->next = new;
    }
  return (EXIT_SUCCESS);
}

int		rm_chan(t_chan **chan, char *chan_name)
{
  t_chan	*tmp;
  t_chan	*rm;

  if (!(*chan))
    return (EMPTY_CHAN_LIST);
  tmp = *chan;
  if (!(*chan)->next)
    *chan = NULL;
  else
    {
      while (tmp)
	{
	  if (tmp->next && strcmp(tmp->next->_chan, chan_name) == 0)
	    {
	      rm = tmp->next;
	      tmp->next = tmp->next->next;
	      memset(rm->_chan, 0, sizeof(rm->_chan));
	      free(rm);
	    }
	  tmp = tmp->next;
	}
    }
  return (EXIT_SUCCESS);
}

void		add_user_to_chan(t_chan **c, char *chan, int fd, char *nickname)
{
  t_chan	*tmp;

  tmp = *c;
  while (tmp)
    {
      if (strcmp(tmp->_chan, chan) == 0)
	{
	  memset(tmp->users[fd], 0, MAX_NICK);
	  strcpy(tmp->users[fd], nickname);
	}
      tmp = tmp->next;
    }
}

void		rm_user_to_chan(t_chan **c, char *chan, int fd)
{
  t_chan	*tmp;

  tmp = *c;
  while (tmp)
    {
      if (strcmp(tmp->_chan, chan) == 0)
	memset(tmp->users[fd], 0, sizeof(tmp->users[fd]));
      tmp = tmp->next;
    }
}
