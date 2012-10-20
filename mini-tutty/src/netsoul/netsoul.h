#ifndef   	NETSOUL_H_
# define   	NETSOUL_H_

#include <buffers/buffers.h>
#include "md5_linux.h"
#include "url.h"

typedef struct
{
  int   lu;
  char* login;
  char* msg;
} nsform;

void  tt_nsconnect(char* hostname,
		   short port,
		   char* passwd,
		   char* login);

void  printip(char* HostName);

char* tt_cut (char* s, int i, char d);

char* tt_nsreceive(void);

void  tt_nsgetinfo(char* login);

void  tt_nssendmsg(char* login,
		   char* msg);

void  tt_nsverif(nsform* formu,
		 nsform* depart);

#endif 	    /* !INCLUDE_H_ */
