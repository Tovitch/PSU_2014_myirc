/*
** check_nick.c for myirc in /home/kruszk_t/Documents/PSU/MyIRC
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Jul  8 11:16:03 2015 Tony Kruszkewycz
** Last update Wed Jul  8 11:16:34 2015 Tony Kruszkewycz
*/

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
