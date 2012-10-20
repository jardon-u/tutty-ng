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



int tutti_send_file(char * ip,char * fichier, int nb_bytes)
{
  FILE * fp;
  char * buf;
  int i=0,j=0,k=0,tampon_secondes=0,nboct=0,vitesse,sockfd;
  time_t t0,t1,t2; 
  t_socket adresse;  

  sockfd=tutti_connect(ip,1773);
  sleep(1);
  tutti_send_msg(sockfd,"1");

  
  if ((fp=fopen(fichier,"r")))  /* ouverture du fichier a envoyer */
  {
    printf("opened\n");
    buf=malloc(sizeof(char)*nb_bytes);
    time(&t0);
    t1=t0;
    while (!feof(fp))
    {
      i=fread(buf,sizeof(char),nb_bytes,fp);
      j++;
      nboct+=write(sockfd,buf,i);
      if (k++>100) 
      {       
        if (t2-t1!=tampon_secondes){ printf("Temp ecoule :%d secondes\n",tampon_secondes);
        tampon_secondes=(int)t2-(int)t1;}
        time(&t2);
        if (t2-t1>9)
        {
	        printf("Kb envoyes depuis le demarrage du transfert : %d \nvitesse actuelle: %f\n\n",(int) ((j*32)/1000),(float)(k*32)/(t2-t1));
	        k=0;
          t1=t2;
      	}
      }
    }
  }
  else
    printf("Fichier %s introuvable\n",fichier);
  j=j*32;
  vitesse= (((int)t2-(int)t0)==0)?0:(int) (nboct/1000*((int)t2-(int)t0));
  printf("\n-> Ok bien envoye.\n Vitesse moyenne:%d Ko/s\n-> Taille : %d Ko\n-> Temps total: %d secondes.\n",vitesse ,(int) (nboct/1000), (int)t2-(int)t0);
  free(buf);
  fclose(fp);
  printf("Closed\n");
  free(adresse);
  tutti_deconnect(sockfd);

  return 0;
  
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
  int sockfd,send,n;
  char buffer[255];
  
  if (argc<2)
  {
    printf("Pas assez de parametres.\n");
    exit(0);
  }
  else
    printf("Connexion au port %s ...\n",argv[1]);
  
  sockfd=tutti_connect("192.168.0.106",strtoint(argv[1]));
  tutti_send_msg(sockfd,"1");
  
  /* communication cycle */
  while (buffer[0]!='0')
  {
    printf("Entrez votre message: "); 
    fgets(buffer,255,stdin);
    send=tutti_send_msg(sockfd,buffer); /* Sending messages */ 
    if (send)
      printf("envoye : %s\n",buffer);
    else
      printf("echec de l'envoi.\n");
    
    n=read(sockfd,buffer,255); /* Checking messages */
    if (n>0)
    {
      buffer[n+1]='\0';
      printf("Vous avez un message : %s\n",buffer);
    }
  }
  
  printf("Fin de la discussion");
 

  tutti_deconnect(sockfd);
  
  return 0;
}
