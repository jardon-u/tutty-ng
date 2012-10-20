#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "lib/chaines.h"

char * concat(char * s1, char * s2);
int longueur(char * s);
int TF_serveur(int buffersize);


/* struct sockaddr_in { */
/*    short   sin_family;		 Address family (type) */
/*    u_short sin_port;		        Port to connect to	 */
/*    struct  in_addr sin_addr;	Host's adress	 */
/*    char    sin_zero[8];	       padding, ignored	 */
/*}; */


/*typedef struct
{
  char * s;
  int t;
  int p;
}msn_string;*/


int TF_serveur(int buffersize)
{
  struct sockaddr_in client;
  int sock, newsock;
  unsigned int lng;
  struct sockaddr_in confserv;
  char * buffer;
  FILE * fichier;
  int i, taille_nom;
  time_t t1, t2;
  char * nom;

  confserv.sin_addr.s_addr	= htonl(INADDR_ANY);
  confserv.sin_family		= AF_INET;
  confserv.sin_port		= htons(1337);

  if ((sock = (socket(AF_INET, SOCK_STREAM, 0))) < 0)
    printf("Erreur\n");
  else
    printf("Socket created !\n");

  if (bind(sock, (struct sockaddr *) &confserv, sizeof(confserv)) < 0)
    printf("Error while binding socket\n");
  else
    printf("Socket bound\n");

  listen(sock, 10);
  printf("Waiting for clients...\n");
   
  lng = sizeof(struct sockaddr_in);
  if ((newsock = accept(sock, (struct sockaddr *) &client, &lng)) < 0)
    return -1;
  
  while (1)
    if (client.sin_family > 0)
      {
  	printf("client familly:%d\n", client.sin_family);
  	break;
      }
  buffer = malloc(buffersize *2* sizeof(char));
  
  taille_nom = longueur("bufferfile");
  nom = malloc(taille_nom * 2 * sizeof(char));
  strcpy(nom,"bufferfile");
  fichier = fopen(concat("/home/ezekiel/projet/", nom), "w+");
  
  /*(void) time(&t1);*/
  while (1)
  {
    i = read(newsock, buffer, buffersize * sizeof(char))
    if (i!=0)
    {
      printf("resultat de read: %d\n", i);
      printf("contenu du buffer %s\n", buffer);
     /* fwrite(buffer, sizeof(char), i, fichier);*/
    }
  }
  
  free(buffer);
  fclose(fichier);
  (void) time(&t2);
  printf("temps ecoule %li\n", (int) t2-t1);
  free(nom);
  return 0;
}

int main()
{
  TF_serveur(128);
  return 0;
}

