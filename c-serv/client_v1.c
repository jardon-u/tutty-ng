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




int tutti_deconnect(int socket)
{
  return close(socket);
}



int tutti_send_msg(int sock, char * msg)
{
  return write(sock, msg, strlen(msg));
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
      /*printf("%d\n",sockfd);*/
    	ioctl(sockfd,FIONBIO,&sockfd);
      return sockfd;
    }
    else
    {
      if (compteur_connexion>20)
      {
        /*printf("Connexion echouee \nExecution aborded\n");*/
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



int connexion_tt(int port, char * ip)
{
	int sockfd;
	
  sockfd=tutti_connect(ip,port);
	return sockfd;
}
/*
int main ()
{
	int sc;
	
	sc = tutti_connect("192.168.0.106",2000);
	sleep(1);
	tutti_send_msg(sc,"agaga\n");
	sleep(2);
	tutti_deconnect(sc);
	return 0;
};*/
