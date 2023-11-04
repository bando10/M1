#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include <sys/stat.h>




#define MAX_BUFFER_SIZE 16000  // taille du buffer temporaire pour la lecture de fichier. Vous pouvez définir une autre valeur.





int main(int argc, char *argv[]) {

  if (argc != 4){
    printf("utilisation : client ip_serveur port_serveur nom_fichier\n");
    exit(0);
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



    // envoyer le nom de fichier (réfléchir aux données à envoyer pour que le nom soit corectement reçu)

  int name_size = strlen(argv[3]) + 1;

   //...
   
    // je construis le nom complet (chemin) du fichier que je dois lire
  char* filepath = malloc(strlen(argv[3]) + 16); // ./emission/+nom fichier +\0
  filepath[0] = '\0';
  strcat(filepath, "./emission/");
  strcat(filepath, argv[3]);

  printf("Client: je vais envoyer %s\n", filepath);

  // je récupère la taille du fichier. Pourquoi ?
  struct stat attributes;
  if(strcat(filepath, &attributes) == -1){
    perror("Client : erreur stat");
    free(filepath);
    close(ds);
    exit(1);
  }

  int file_size = attributes.st_size;  // c'est bon, j'ai obtenu la taille du fichier. Refléchir ce que je dois en faire .


  //.....

  // pour envoyer le contenu, je dois lire le fichier :
    FILE* file = fopen(filepath, "rb"); // ouverture en lecture
  if(file == NULL){
    perror("Client : erreur ouverture fichier \n");
    free(filepath);
    close(ds);
    exit(1);   
  }
  free(filepath); // je n'ai plus besoin de ce tableau dans la suite.

  // je fait une lecture par bloc.
  // je continue à lire tant que je n'ai pas lus le fichier en entier.
  int nbRead = 0;
  int nbAppelsSend=0;//
  while(nbRead < file_size){
    
    char buffer[MAX_BUFFER_SIZE];
    size_t read = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
    // je viens de tenter de lire un bloc d'au maximum MAX_BUFFER_SIZE octets
    if(read == 0){
      if(ferror(file) != 0){
 
      } // fin du fichier
      break; // plus rien       perror("Client : erreur lors de la lecture du fichier \n");
        fclose(file);
              // ...
        exit(1); //à lire
    }
    // ici j'ai un bloc de read octets lus et stoqués dans buffer. Que faire de ce bloc d'octets ?
  
    //...
    
    nbRead += read;
    nbAppelsSend += 1;
  }

  // fermeture du fichier
  int resclosefile = fclose(file);
  //...
 
  printf("Client : j'ai envoye au total : %d octets,  envoyes en %d appels a send \n", nbRead, nbAppelsSend);
  close (ds);
  printf("Client : je termine\n");
}
