#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, char *argv[]) {

  /* je passe en paramètre l'adresse de la socket du serveur (IP et
     numéro de port) et un numéro de port à donner à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 4){
    printf("utilisation : %s ip_serveur port_serveur port_client\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
    perror("Client : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }

  /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Client : creation de la socket réussie \n");

  // Je peux tester l'exécution de cette étape avant de passer à la
  // suite. Faire de même pour la suite : n'attendez pas de tout faire
  // avant de tester.

  /* Etape 2 : Nommer la socket du client */
  struct sockaddr_in sockClient;
  sockClient.sin_family = AF_INET;
  sockClient.sin_addr.s_addr = inet_addr(argv[1]);
  sockClient.sin_port = htons((short)atoi(argv[2]));

  socklen_t lgA = sizeof(struct sockaddr_in);
  int resc = connect(ds, (struct sockaddr*)&sockClient, lgA);

  if(resc == -1){
      perror("Erreur connection");
      exit(1);
  }

  int nb_msg;
  printf("Client : Combien de message a envoyer ? : ");
  scanf("%d", &nb_msg);
  ssize_t res = send(ds, &nb_msg, sizeof(int), 0);
  if(res < 0){
      perror("Client : erreur a l'envoi : ");
      exit(1);
  }


  //getchar();

  for(int i=1; i<=nb_msg; i++){
      char m[1000];
      printf("Message n°%d : \n", i);
      fgets(m, sizeof(m), stdin);
      ssize_t res = send(ds, &m, sizeof(m), 0);
      printf("Client : nombre d'octets envoyes : %d \n", (int)res);
  }


  close(ds);
  printf("Client : je termine\n");
  return 0;
}