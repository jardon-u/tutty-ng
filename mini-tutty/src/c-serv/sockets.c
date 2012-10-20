#include"client_lib.h"

int send_msg(int sock, char * msg)
{
  char * tmp;

  tmp=msg;

  write(sock, msg, 16);

  return 0;
}



int main()
{
/*  send_file("81.64.78.51","/home/leove/meup.mp3",128); */
  int sockfd;

  sockfd=initialize_socket("192.168.0.106",1337);
/*  tt_send_file(sockfd,"/home/leove/taff/proj/reseau/sockets/exemple_client",32);*/
  /*tt_send_file(sockfd,"/home/leove/Desktop/mac_lol.avi",32);*/

  send_msg(sockfd,"coucou");
  
  
 /*   write(sockfd,"1fichiai.txt",32); */

  finalize_socket(sockfd);
  
  return 0;
}
