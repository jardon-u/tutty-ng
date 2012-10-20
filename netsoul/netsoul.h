#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <string.h>
#include "md5_linux.h"
#include "../buffers/buffers.h"
#include "url.h"

typedef struct
{
  int lu;
  char * login;
  char * msg;
}nsform;

void tt_nsconnect(char * hostname, short port, char * passwd, char * login);
void printip(char* HostName);
char * tt_cut (char * s,int i,char d);
char * tt_nsreceive();
void tt_nsgetinfo(char * login);
void tt_nssendmsg(char * login, char * msg);
void tt_nsverif(nsform * formu, nsform * depart);
