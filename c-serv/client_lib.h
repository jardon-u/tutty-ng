#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
#include<string.h>

typedef struct sockaddr_in * t_socket;

char * tutti_recv_msg(int sock);
int tutti_send_file(char * ip_destinataire,char * fichier, int nb_bytes);
int tutti_connect(char * ip_dest,int port);
int tutti_send_msg(int sock, char * msg);
int tutti_send_file(char * ip,char * fichier, int nb_bytes);
int tutti_deconnect(int socket);


