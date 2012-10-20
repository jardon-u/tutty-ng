#include "netsoul.h"

nsform formu, depart;

int main()
{ 
  formu.lu = 1;
  tt_nsconnect("ns-server.epita.fr", 4242, "EdzC*nO4", "poulai_f");
  /*tt_nsgetinfo("poulai_f");*/
  /*tt_nssendmsg("poulai_f", "si ce message apparaît, c'est gut");*/
  depart.lu = 0;
  depart.login = malloc(9);
  depart.msg = malloc(18);
  strcat(depart.login, "poulai_f");
  strcat(depart.msg, "teste de messageu");
  tt_nssendmsg("poulai_f", "tonku");
  
  while (1)
    {
      tt_nsverif(&formu, &depart);
      printf("pwet\n");
      if (!formu.lu)
	{
	  printf("\nMessage de %s:\n%s\n", formu.login, url_decode(formu.msg));
	  formu.lu = 1;
	}
      sleep(1);
    }
  return 0;
}
