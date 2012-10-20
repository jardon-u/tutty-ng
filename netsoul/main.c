#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "url.h"
#include "md5_linux.h"

int main()
{
  MD5_CTX context;
  char *password;
  char * pass;
  char ** b;

  pass = malloc(100);
  b = malloc(sizeof(char **));
  
  asprintf(b, "%s-%s/%s%s", "0d64671c9909ddf23915778eaf52e05c","82.234.245.124", "48037", "2JIwe4=O");
  printf("%s\n", *b);
  
  MD5Init(&context);
  MD5Update(&context, *b, strlen(*b));
  password = MD5End(&context, pass);
  
  printf("%s\n", password);
  printf("%s\n", pass);
}
