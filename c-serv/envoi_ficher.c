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
  int sockfd,n=0;
  char buffer[255];

  sockfd=tutti_connect("192.168.0.106",1338);
  sleep(1);
  printf("sent:%d\n",tutti_send_msg(sockfd,"2")); /* file transfert */
  
  while(1) /* communication cycle */
  {
    printf("Entrez votre message: ");
    while (fgets(buffer,255,stdin))
      n = tutti_send_msg(sockfd,buffer);
    
    n=read(sockfd,buffer,255);
    buffer[n+1]='\0';
    printf("Vous avez un message : %s\n",buffer);
  }

  finalize_socket(sockfd);
  
  return 0;
}
