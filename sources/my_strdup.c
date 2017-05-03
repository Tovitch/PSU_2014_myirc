/*
** my_strdup.c for myirc in /home/kruszk_t/rendu/PSU_2014_myirc
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Apr  1 11:44:38 2015 kruszk_t
** Last update Wed Apr  1 11:49:03 2015 kruszk_t
*/

#include	<string.h>
#include	<stdlib.h>

char		*my_strdup(char *str)
{
  char		*ret;

  if (!(ret = malloc(sizeof(char) * strlen(str))))
    return (NULL);
  strcpy(ret, str);
  return (ret);
}
