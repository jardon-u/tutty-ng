#include <stdlib.h>
#include "buffers.h"

void charad(msn_string * s,char c)
{
  if (s->t==0)
    {
      s->s=malloc(11);
      s->t=10;
      s->p=0;
    }
  if (((s->p)+1)%10==0)
    {
      s->t+=10;
      s->s=realloc(s->s,s->t+1);
    }
  *((s->s)+(s->p))=c;
  s->p+=1;
}

void stringadd(msn_string * s,char * str)
{
  int i;

  i=0;
  while (*(str+i)!='\0')
    {
      charad(s,*(str+i));
      i++;
    }
  charad(s,'\0');
}
