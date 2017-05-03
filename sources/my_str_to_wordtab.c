/*
** my_str_to_wordtab.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr  1 13:41:34 2015 kruszk_t
** Last update Wed Jul  8 15:32:48 2015 Tony Kruszkewycz
*/

#include	<stdlib.h>
#include	<string.h>

void		delete_tab(char **tab)
{
  int		i;

  for (i = 0; tab[i]; ++i)
    free(tab[i]);
  free(tab);
}

static int	nb_word(char *str)
{
  int		i;
  int		count;

  count = 1;
  for (i = 0; str[i]; ++i)
    {
      if (str[i] == ' ')
	++count;
    }
  return (count + 1);
}

static int	word_len(char *str, int i)
{
  int		count;

  count = 0;
  while (str[i] && str[i] != ' ')
    {
      ++count;
      ++i;
    }
  return (count);
}

char		**my_str_to_wordtab(char *str)
{
  char		**tab;
  int		i;
  int		x;
  int		y;
  int		sz;

  if (!str || str[0] == '\0')
    return (NULL);
  sz = strlen(str);
  if (!(tab = malloc(sizeof(char *) * nb_word(str) + 1)))
    return (NULL);
  for (i = 0, y = 0, x = 0; i < sz; ++y)
    {
      for (; str[i] == ' ' || str[i] == '\t'; ++i);
      if (!(tab[y] = malloc(sizeof(char) * word_len(str, i) + 1)))
	return (NULL);
      for (x = 0; str[i] && str[i] != ' '; ++i, ++x)
	tab[y][x] = str[i];
      tab[y][x] = 0;
      ++i;
    }
  tab[y] = NULL;
  return (tab);
}
