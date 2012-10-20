/*
** url.c for  in /home/dev/NoSoucy-0.3
** 
** Made by Anto
** Login   <root@epita.fr>
** 
** Started on  Thu May 22 01:52:15 2003 Anto
** Last update Thu May 22 02:09:41 2003 Anto
*/

#define _GNU_SOURCE
#include "url.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char    *strip_return(char *str)
{
  int		cpt[2];

  for (cpt[0] = cpt[1] = 0; str[cpt[0]]; cpt[0]++, cpt[1]++)
    if (str[cpt[0]] == '\\' && str[cpt[0] + 1] && str[cpt[0] + 1] == 'n')
      {
        str[cpt[1]] = '\n';
	cpt[0]++;
      }
    else
      str[cpt[1]] = str[cpt[0]];
  str[cpt[1]] = 0;
  return (str);
}

char    *url_decode(char *str)
{
  int   cpt[2];
  char  nb[5];

  memset(nb, 0, 5);
  for (cpt[0] = cpt[1] = 0; str[cpt[0]]; cpt[0]++, cpt[1]++)
    if (str[cpt[0]] == '%' && str[cpt[0] + 1] &&
        ((str[cpt[0] + 1] >= '0' && str[cpt[0] + 1] <= '9') ||
         (str[cpt[0] + 1] >= 'A' && str[cpt[0] + 1] <= 'F') ||
         (str[cpt[0] + 1] >= 'a' && str[cpt[0] + 1] <= 'f')))
      {
        sprintf(nb, "0x%.2s", str + cpt[0] + 1);
        str[cpt[1]] = strtol(nb, 0, 16);
	cpt[0] += 2;
      }
    else
      str[cpt[1]] = str[cpt[0]];
  str[cpt[1]] = 0;
  str = strip_return(str);
  return (str);
}

char    *url_encode(unsigned char *str)
{
  char  *encoded;
  char	*tmp;
  
  for (encoded = strdup(""); str && *str; str++)
    {
      tmp = encoded;
      if ((*str >= 'a' && *str <= 'z') ||
	  (*str >= 'A' && *str <= 'Z') ||
	  (*str >= '0' && *str <= '9') ||
	  *str == '_' || *str == '-' || *str == '.')
	asprintf(&encoded, "%s%c", encoded, *str);
      else
	asprintf(&encoded, "%s%%%02X", encoded, *str);
      free(tmp);
    }
  return (encoded);
}
