/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>



void tutti_discuss(int);
void tutti_receiv_file(int);


void error(char *msg)
{
    perror(msg);
    exit(1);
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

int main(int argc, char *argv[])
{
  int sockfd, sck_qqun, pid,i;
  unsigned int clilen;
  struct sockaddr_in serv_addr, cli_addr;
  char buffer[256];
     
  if (argc<2)
  {
    printf("Pas assez de parametres.\n");
    exit(0);
  }
  else
    printf("Connexion au port %s ...\n",argv[1]);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
	ioctl(sockfd,FIOSNBIO,&sockfd);
  if (sockfd < 0) 
    error("ERROR opening socket");
/*     bzero((char *) &serv_addr, sizeof(serv_addr));*/
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(strtoint(argv[1]));
  if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
  listen(sockfd,5);
  clilen = sizeof(cli_addr);
  printf("\nServeur operationel\n");
  while (1) 
  {
		/*
    printf("Attente d'une connexion...\n");
    sck_qqun = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
    if (sck_qqun >= 0)
      printf("IP client : %s\n", inet_ntoa(cli_addr.sin_addr));
		else
      printf("%s\n", inet_ntoa(cli_addr.sin_addr));
    */
		printf("%d",select(FD_SETSIZE, &fd, NULL, NULL, &tv));
		/*
       
    if (sck_qqun < 0)
      error("ERROR on accept");
    pid = fork();
    if (pid < 0)
         error("ERROR on fork");
    if (pid == 0)  
    {
      printf("Fils cree - ");
      close(sockfd);
      while ((i=read(sck_qqun,buffer,10))<=0)
	   sleep(0.1);
      switch (buffer[0])
      {
        case '1':
	      {
	        printf("Mode discussion\n");
          tutti_discuss(sck_qqun);
	        close(sck_qqun);
	        break;
	      }  
        case '2':
	      {
	        printf("Mode transfert\n");
          tutti_receiv_file(sck_qqun);
	        break;
	      }  
      }
      printf("Cloture du fils\n");
      exit(0);
    }
    else 
    {
      printf("Le pere ferme le socket\n");
      close(sck_qqun);
    }*/
		
  } 
  return 0;
}


void tutti_receiv_file(int sock)
{
  sock++;
}

void tutti_discuss(int sock)
{
   int n;
   char buffer[256];
      
   /*bzero(buffer,256);*/
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
     
/*       while (i<255)
       fgets(buffer[i++],1,stdin);
       send=tutti_send_msg(sockfd,buffer);*/
     }
   }
   printf("fin de traitement du fils - ");
   /*n = write(sock,"I got your message",18);
   if (n < 0) error("ERROR writing to socket");*/
}

