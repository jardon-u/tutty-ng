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
    	ioctl(sockfd,FIONBIO,&sockfd);
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

char * tutti_recv_msg(int sock)
{
	char * buffer;
  
	buffer=malloc(sizeof(char)*255);
	if (read(sock,buffer,255)>0)
		return buffer;
  else
		return NULL;	
}

int main(int argc, char *argv[])
{
  int sockfd,send;/*,n;*/
  char buffer[255];
	char *msg;
  
  if (argc<2)
  {
    printf("Pas assez de parametres.\n");
    exit(0);
  }
  else
    printf("Connexion au port %s ...\n",argv[1]);
  
  sockfd=tutti_connect("192.168.0.106",strtoint(argv[1]));
  
  /* communication cycle */
  while (1)
  {
		msg=tutti_recv_msg(sockfd);
		if (msg!=NULL)
			printf("Message recu : %s\n",msg);
    printf("Entrez votre message: "); 
    fgets(buffer,255,stdin);
		
	printf("a\n");

    send=tutti_send_msg(sockfd,buffer); 
    if (send)
      printf("envoye : %s\n",buffer);
    else
      printf("echec de l'envoi.\n");
    
/*    n=read(sockfd,buffer,255);  Checking messages 
    if (n>0)
    {
      buffer[n+1]='\0';
      printf("Vous avez un message : %s\n",buffer);
    }*/
	}
  
  printf("Fin de la discussion");
 

  tutti_deconnect(sockfd);
  
  return 0;
}
