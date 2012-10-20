#ifndef BUFFERS_H
#define BUFFERS_H
typedef struct
{
  char * s;
  int t;
  int p;
}msn_string;

void charad(msn_string * s,char c);

void stringadd(msn_string * s,char * str);
#endif
