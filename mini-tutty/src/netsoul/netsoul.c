#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "netsoul.h"

int sockfd;

void tt_nsconnect(char * hostname, short port, char * passwd, char * login)
{
  struct sockaddr_in srv;
  struct hostent*    host;
  struct in_addr**   adr;

  char*  password;
  char** b;
  char*  pass;
  char*  bfout;

  my_MD5_CTX context;
  msn_string str;
  
  srv.sin_family = AF_INET;
  srv.sin_port = htons(port);
  
  if ((host = gethostbyname(hostname)) != NULL)
    for (adr=(struct in_addr **)host->h_addr_list; *adr; adr++)
      {
	srv.sin_addr.s_addr = inet_addr(inet_ntoa(**adr));
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(sockfd,
		    (const struct sockaddr *) &srv,
		    sizeof(srv)) < 0)
	  printf("erreur\n"); /* FIXME : guiprint */
	else
	  {
	    printf("connected to:\n  %s (%s)\n", inet_ntoa(**adr), hostname);
	    printf("sockfd: %i\n", sockfd);
	    break;
	  }
      }
  
  ioctl(sockfd, FIONBIO, &sockfd);
  
  str.s = malloc(500);
  strcpy(str.s, tt_nsreceive());
  printf("caca:  %s\n", str.s);
  
  b = malloc(sizeof(char **));
  asprintf(b, "%s-%s/%s%s", tt_cut(str.s, 3, ' '), tt_cut(str.s, 4, ' '), tt_cut(str.s, 5, ' '), passwd);
  printf("%s\n", *b);
  my_MD5Init(&context);
  my_MD5Update(&context, *b, strlen(*b)); /* FIXME : warning */
  pass = malloc(100);
  password = MD5End(&context, pass);
  printf("%s\n", password);
  
  bfout = malloc(28);
  *bfout = '\0';
  strcat(bfout, "auth_ag ext_user none none\n");
  printf("%s %i\n", bfout, strlen(bfout));
  send(sockfd, bfout, strlen(bfout), 0);

  tt_nsreceive();
  
  send(sockfd, "ext_user_log ", 13, 0);
  send(sockfd, login, strlen(login), 0);
  send(sockfd, " ", 1, 0);
  send(sockfd, password, strlen(password), 0);
  send(sockfd, " none location\n", 15, 0); 
  printf("authentication information sent...\n");
  tt_nsreceive();
  
  return;
}


void printip(char* HostName)
{
  struct hostent *host;
  struct in_addr **adr;
  
  if((host = gethostbyname(HostName)) != NULL)
    {
      for (adr=(struct in_addr **)host->h_addr_list; *adr; adr++)
	{
	  printf("IP : %s\n", inet_ntoa(**adr));
	}
    }
  else
    {
      printf("Echec de la resolution de nom\n");
    }
}


char * tt_cut (char * s,int i,char d)
{
  int j;
  msn_string ns;
  
  j=0;
  while (i>1) if (*(s+j++) == d) i--;
  ns.t=0;
  while ((*(s+j)!=d) && (*(s+j)!='\r') && (*(s+j)!='\n') && (*(s+j)!='\0')) 
    charad(&ns,*(s+j++));
  charad(&ns,'\0');
  return ns.s;
}


char* tt_nsreceive(void)
{
  msn_string str;
  char bfin;

  str.t = 0;
  bfin = 0;
  recv(sockfd, &bfin, 1, 0);
  while (bfin != '\n')
    { 
      if (bfin != 0)
	charad(&str, bfin);
      bfin = 0;
      recv(sockfd, &bfin, 1, 0);
    }
  charad(&str, '\0');
  /*printf("%s\n", str.s);*/
  return str.s;
}


void tt_nsgetinfo(char * login)
{
  send(sockfd, "list_users {", 12, 0);
  send(sockfd, login, strlen(login), 0);
  send(sockfd, "}\n", 2, 0);
}


void tt_nssendmsg(char* login,
		  char* msg)
{
  char* encmsg;
  encmsg = url_encode(msg);
  
  send(sockfd, "user_cmd msg_user", 17, 0);
  send(sockfd, " ", 1, 0);
  send(sockfd, login, strlen(login), 0);
  send(sockfd, " msg ", 5, 0);
  send(sockfd, encmsg, strlen(encmsg), 0);
  send(sockfd, "\n", 1, 0);
}

void tt_nsverif(nsform * formu, nsform * depart)
{
  msn_string str;
  char bfin;
  
  if (!depart->lu)
    {
      tt_nssendmsg(depart->login, depart->msg);
      depart->lu = 1;
    }
  
  if (!formu->lu)
    return;
  
  str.t = 0;
  bfin = 0;
  if (recv(sockfd, &bfin, 1, 0) <= 0)
    return;
  while (bfin != '\n')
    {
      if (bfin != 0)
	charad(&str, bfin);
      bfin = 0;
      recv(sockfd, &bfin, 1, 0);
    }
  charad(&str, '\0');
  
  if (str.t == 0)
    return;
  else
    {
      if (strstr(str.s, "msg"))
	{
	  /*free(formu->login);
	    free(formu->msg);*/
	  formu->lu = 0;
	  /*formu->login = malloc(strlen(tt_cut(tt_cut(str.s, 4, ':'), 1, '@')) + 1);
	    formu->msg = malloc(strlen(tt_cut(str.s, 5, ' ')) + 1);*/
	  formu->login = tt_cut(tt_cut(str.s, 4, ':'), 1, '@');
	  formu->msg = url_decode(tt_cut(str.s, 5, ' '));
	}
    }
}
