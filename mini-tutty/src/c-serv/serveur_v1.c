/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection

   verifie_connexions
	 recupere_connexion

	 
	 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int cl_list[5];

int socket_de_connexion;
struct sockaddr_in cli_addr;

t_contact * listing;

void tutti_discuss(int);
void tutti_receiv_file(int);


void error(char *msg)
{
    perror(msg);
    exit(1);
}


int init_socket_reception()
{
  struct sockaddr_in serv_addr;
	
  socket_de_connexion = socket(AF_INET, SOCK_STREAM, 0);
	
	ioctl(socket_de_connexion,FIONBIO,&socket_de_connexion);
	
  if (socket_de_connexion < 0) 
    error("ERROR opening socket");
/*     bzero((char *) &serv_addr, sizeof(serv_addr));*/
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(2000);
  if (bind(socket_de_connexion, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
  listen(socket_de_connexion,5);
/*     bzero((char *) &serv_addr, sizeof(serv_addr));*/
  printf("\n\nServeur operationel\n");


  return socket_de_connexion;
}

int verifie_connexions()
{
  fd_set fd;
	struct timeval tv;
		
  FD_ZERO(&fd);
  FD_SET(socket_de_connexion, &fd);
  tv.tv_sec = 0;
  tv.tv_usec = 10;
	return select(FD_SETSIZE, &fd, NULL, NULL, &tv);
}

int recupere_connexion()
{
	unsigned int clilen;

	clilen=sizeof(cli_addr);
	return accept(socket_de_connexion,(struct sockaddr *) &cli_addr, &clilen);
}
/*
int main(int argc, char *argv[])
{
  int sockfd, check_sock=0, sck_qqun, high_sock=0,n,i,flag;
	char buffer[255];

	for (i=0;i<5;i++)
	cl_list[i]=0;
     
  if (argc<2)
  { printf("Pas assez de parametres.\n"); exit(0); }
  else printf("Connexion au port %s ...\n",argv[1]);

  sockfd = init_socket_reception();
	printf("Socket de connexion : %d",socket_de_connexion);
	
  if (socket_de_connexion < 0) 
    error("ERROR opening socket");*/
/*     bzero((char *) &serv_addr, sizeof(serv_addr));*//*
  printf("\n\nServeur operationel\n");
	
  while (1) 
  {
		check_sock=verifie_connexions();
		if (check_sock>0)
		{
			printf("Select : %d\n",check_sock);
			printf("Client present : ");
      sck_qqun = recupere_connexion();
    	ioctl(sck_qqun,FIONBIO,&sck_qqun);

      printf("%d :: %s\n",sck_qqun, inet_ntoa(cli_addr.sin_addr));
			i=0;
			while ((i<5) && (cl_list[i]!=0)) i++;
			if (i>4) printf("lsit full\n");
			else cl_list[i]=sck_qqun;
		}
		else
		{
			high_sock=0;
			for (i=0;i<5;i++)
				if (cl_list[i]>0) high_sock++;
			if (high_sock>0)
			for (i=0;i<5;i++)
			{
				if (cl_list[i]!=0)
				{
			  	n=read(cl_list[i],buffer,255);

					switch (n)
					{
						case 0:
						{
							printf("Client %d : a ferme sa fenetre\n",i);
			        printf("Etat : \n%d clients connectes \n",--high_sock);
	  					close(cl_list[i]);
		  				cl_list[i]=0;
							break;
						}
						case -1:
						{
							if (flag)
							{
  							printf("Client %d : pas de msg\n",i);	
								printf("Etat : \n%d clients connectes \n",high_sock);
  							flag=0;
							}
							break;
						}
						default:
						{
							buffer[n]='\0';
  				    printf("Client %d : %s\n",i,buffer);
							write(cl_list[i],"recu",strlen("recu"));
							flag=1;
							break;
			  		}
					}
				}
			}
  	 	fflush(stdout);
		}
  } 
  return 0;
}
*/
/*
void tutti_receiv_file(int sock)
{
  sock++;
}

void tutti_discuss(int sock)
{
   int n;
   char buffer[256];
      */
   /*bzero(buffer,256);*//*
   printf("en reception\n");
   while (((n = read(sock,buffer,255))>=0) && (buffer[0]!='0'))
   {
     sleep(0.5);
     printf(" ------------------ \n");
     if (n>0)
     {
       buffer[n]='\0';
       printf("Message[%d] recu par fils[%d] : %s",n,getpid(),buffer);
       printf("Repondre ? o/n");
       fgets(buffer,8,stdin);
       if (buffer[0]=='o')
       {
         printf("Tapez la reponse :");
         fgets(buffer,255,stdin);
	 if (write(sock,buffer,strlen(buffer)))
           printf("Message envoye\n");
	 else
	   printf("Echec de l'envoi\n");
       }
     */
/*       while (i<255)
       fgets(buffer[i++],1,stdin);
       send=tutti_send_msg(sockfd,buffer);*//*
     }
   }
   printf("fin de traitement du fils - ");*/
   /*n = write(sock,"I got your message",18);
   if (n < 0) error("ERROR writing to socket");*//*
}*/

