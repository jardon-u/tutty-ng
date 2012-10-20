#include"client_lib.h"

/*  - int tutti_connect(ip,port)                         *
 *      establish a connection between client & serv     *
 *      returns the socket created, -1 if failed         *
 *                                                       *
 *  - int tutti_deconnect(socket)                        *
 *      close the socket returned by tutti_connect()     *
 *      returns -1 if failed                             *
 *                                                       *
 *  - tutti_send_msg(socket,msg)                         *
 *      sends msg into socket                            *
 *      returns -1 if failed                             *
 *                                                       *
 *  - tutti_send_file(socket,path)                       *
 *                                                       */


int tutti_send_msg(int sock, char * msg)
{
  return write(sock, msg, strlen(msg));
}


int strtoint(char * str)
{
  int i=0,n=0;

  while (str[i]!='\0')
  {
    n=n*10+(str[i]-48);
    i++;
  }
  return n;
}


int tutti_connect(char * ip_dest,int port)
{
  int sockfd, compteur_connexion=0;
  t_socket sock, adresse;  
  
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  sock    = malloc(sizeof(struct sockaddr_in));
  adresse = malloc(sizeof(struct sockaddr_in));

  adresse->sin_addr.s_addr	= inet_addr(ip_dest);
  adresse->sin_family		= AF_INET;
  adresse->sin_port		= htons(port);

  /*-- BODY --*/
  while (++compteur_connexion)
  {
    sleep(1);
    if (connect(sockfd,(struct sockaddr *) adresse, sizeof(struct sockaddr_in)) >= 0)
    {
      printf("%d\n",sockfd);
      return sockfd;
    }
    else
    {
      if (compteur_connexion>20)
      {
        printf("Connexion echouee \nExecution aborded\n");
        exit(0);
      }

    }
  }

  return sockfd;
}



int main(int argc, char *argv[])
{
  int sockfd,n;
  
  if (argc<2)
  {
    printf("Pas assez de parametres.\n");
    exit(0);
  }
  else
    printf("Connexion au port %s ...\n",argv[1]);


  sockfd=tutti_connect("192.168.0.106",strtoint(argv[1]));
  n=0;
  while (n++<20)
  {
    sleep(1);
    tutti_send_msg(sockfd,"0");
  }

  
  printf("Fin de la discussion");
 

  tutti_deconnect(sockfd);
  
  return 0;
}
