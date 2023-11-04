#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>

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

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
    perror("Serveur : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }

  /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Serveur : creation de la socket réussie \n");

  // Je peux tester l'exécution de cette étape avant de passer à la
  // suite. Faire de même pour la suite : n'attendez pas de tout faire
  // avant de tester.

  /* Etape 2 : Nommer la socket du seveur */
  struct sockaddr_in sockServer;
  sockServer.sin_family = AF_INET;
  sockServer.sin_addr.s_addr = INADDR_ANY;
  sockServer.sin_port = htons((short)atoi(argv[1]));

  socklen_t lgA = sizeof(struct sockaddr_in);

  printf("Serveur : numero de port de la socket cree : %d \n", ntohs(sockServer.sin_port));

  int res_bind = bind(ds, (struct sockaddr *)&sockServer, sizeof(sockServer));
  if(res_bind == -1){
      perror("Erreur pour faire le bind");
      exit(1);
  }

  int res_listen = listen(ds, 10);
  if(res_listen == -1){
      perror("Erreur ecoute de la part du serveur");
      exit(1);
  }

  // On recupère la socket client
  struct sockaddr_in sockClient;
  int dSClient = accept(ds, (struct sockaddr*)&sockClient, &lgA);
  if(dSClient <= 0){
      perror("Probleme d'acceptation");
      exit(1);
  }

  /* int nb_msg;
  ssize_t res = recv(dSClient, &nb_msg, sizeof(int), 0);
  if(res ==-1){
          perror("Serveur : erreur a la reception ");
          exit(1);
      } else if (res==0){
        perror("socket fermee\n");
        exit(1);
      } */


  /* for(int i=0; i<nb_msg; i++){
      char m[1000];
      ssize_t res = recv(dSClient, &m, sizeof(m), 0);
      if(res ==-1){
          perror("Serveur : erreur a la reception ");
          exit(1);
      } else if (res==0){
        perror("socket fermee\n");
        exit(1);
      }
      {
    
      }
      printf("Serveur : message reçu : %s \n", m);
  } */
  char m[1000];
  ssize_t res;
  while(1){
      //char m[1000];
      res = recv(dSClient, m, sizeof(m), 0);
      if(res ==-1){
          perror("Serveur : erreur a la reception ");
          exit(1);
      } /* else if (res==0){
        perror("socket fermee\n");
        exit(1); */
      }
      m[(int)res]="\0";
      printf("Serveur : message recu de la part de : %s:%d \n", inet_ntoa(sockClient.sin_addr), ntohs(sockClient.sin_port));
      printf("Serveur : message reçu : %s \n", m);
  
  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  close(ds);
  printf("Serveur : je termine\n");
  return 0;
}