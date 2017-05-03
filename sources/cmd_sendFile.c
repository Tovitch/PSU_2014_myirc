/*
** cmd_sendFile.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr 15 16:21:47 2015 kruszk_t
** Last update Wed Jul  8 13:46:53 2015 Tony Kruszkewycz
*/

#include		<stdlib.h>
#include		<stdio.h>
#include		<unistd.h>
#include		<string.h>
#include		<sys/types.h>
#include		<sys/stat.h>
#include		"client.h"

static void		my_sendfile(t_env *e, char **entry, int size)
{
  (void)e;
  (void)entry;
  (void)size;
}

static int		check_login_entry(t_env *e, char **entry)
{
  if (e->sfd == NOT_LOGGED)
    return (NOT_LOG_SRV);
  if (e->chan == NULL)
    return (EMPTY_CHAN_LIST);
  if (entry[1] == NULL || entry[2] == NULL)
    return (SEND_FILE_USAGE);
  return (EXIT_SUCCESS);
}

int			cmd_sendFile(t_env *e, char **entry)
{
  struct stat		st;
  char			tmp[BUF_SZ];
  int			ret;

  if ((ret = check_login_entry(e, entry)) != EXIT_SUCCESS)
    return (ret);
  memset(tmp, 0, sizeof(tmp));
  getcwd(tmp, BUF_SZ);
  sprintf(tmp, "/%s", entry[2]);
  stat(tmp, &st);
  if ((st.st_mode) == S_IFDIR)
    return (BAD_FILE);
  memset(tmp, 0, sizeof(tmp));
  sprintf(tmp, "%s %s %s", entry[0], entry[1], entry[2]);
  write(e->sfd, tmp, strlen(tmp) + 1);
  usleep(500000);
  if (e->state == 0)
    {
      write(2, SEND_FILE_FAILED_MSG, strlen(SEND_FILE_FAILED_MSG));
      return (SEND_FILE_FAILED);
    }
  if (e->state > 3)
    my_sendfile(e, entry, st.st_size);
  e->state = 0;
  return (EXIT_SUCCESS);
}
