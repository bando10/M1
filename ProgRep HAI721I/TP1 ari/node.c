#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include "common.h"
#include "node_interconnexions.h"



int main(int argc, char *argv[]) {

  /* Je passe en paramètre le numéro de port qui sera donné à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 2){
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }

    /* Etape 1 : créer une socket */
  int ds = socket(PF_INET, SOCK_STREAM, 0);



  if (ds == -1){
    perror("Serveur : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }

   /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Serveur : creation de la socket réussie \n");

    /* Etape 2 : Nommer la socket du seveur */
  struct sockaddr_in ad ;
ad.sin_family = AF_INET ;
ad.sin_addr.s_addr = INADDR_ANY ;
ad.sin_port = htons((short)atoi (argv[1])) ; // num ́ero est `a passer en param`etre !
int server = bind(ds, (struct sockaddr*)&ad, sizeof(ad)) ;
if(server==-1){
   printf("server bind error \n");
   exit(1);
}
int tListen=listen(ds,7);
if(tListen==-1){
  perror("probleme d'écoute \n");
  exit(1);
}


  // cet appel cronstruit le réseau complet
  int * lesAutresNoeuds = configuration(argc, argv);


  // algo exclusion mutuelle :
  int indice = atoi(argv[3]);

  fd_set set , settmp;

//Initialise a faux les  eleements de l’ensemble pointe par set
  FD_ZERO(&set);



  //Ajoute le descripteur desc a la liste des descripteurs de *set a scruter, i.e.
  //positionne l’element a l’indice desc  vrai.
  FD_SET(ds,&set);



  int max =ds;

  while (1) {
  settmp=ds;

  select(max+1, &settmp, NULL, NULL, NULL);
  for(int df=2;df<=max;df++){
    if(!FD_ISSET(df,&settmp)){
      continue;;
    }
    if(df==ds){
      int dSC=accept(ds, NULL, NULL);
      FD_SET(dSC,&set);
      if(max<dSC){
        max=dSC;
      }
      continue;
    }
    struct requete req;
    if(recv(df, &req, sizeof(req),0)<=0){
      FD_CLR(df,&set);
      close(df);
      continue;
    }
    int rep=traiter(req);
    send(df, &rep, sizeof(int),0);
  }

  }



  return 0;
}


