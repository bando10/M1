#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>


#define MAX_BUFFER_SIZE 16000 // taille du buffer qui me permet de récupérer le contenu du fichier à recevoir bloc par bloc. Vous pouvez changer cette valeur.



int main(int argc, char *argv[])
{
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
struct sockaddr_in sockClient;
  int dSClient = accept(ds, (struct sockaddr*)&sockClient, &lgA);
  if(dSClient <= 0){
    perror("Probleme d'acceptation");
    exit(1);
    }
char m[1000];
ssize_t res;
while(1){
      //char m[1000];
    res = recv(dSClient, m, sizeof(m), 0);
    if(res ==-1){

 /* boucle pour le traitement itératif des clients */
  while(1){

    int name_size;
    // je doit recevoir des données me permettant d'obtenur le nom d'un fichier
    //...
    
    char* file_name = malloc(name_size);

    //...
    printf("Serveur, je vais recevoir le fichier %s\n", file_name);

    // je construis le chemin vers le fichier à créer.
    char* filepath = malloc(name_size + 16); // ./reception/+nom fichier
    filepath[0] = '\0';
    strcat(filepath, "./reception/");
    strcat(filepath, file_name);
    free(file_name);

  // j'ouvre le fichier dans lequel je vais écrire
    FILE* file = fopen(filepath, "wb");
    if(file == NULL){  // servez vous de cet exemple pour le traitement des erreurs. 
      perror("Serveur : erreur ouverture fichier: \n");
      free(filepath);
      close (dSClient);
      continue; // passer au client suivant 
    }
    
    free(filepath); // je n'en ia plus besoin.

    //reception des données me permettant de recevoir correctement le contenu du fichier.
    int file_size;
  
    //...
      
    int contentReceived = 0; // Compte le nombre d'octets du fichier reçu

    // je reçois le contenu progressivement 
    while(contentReceived < file_size){
      
      char buffer[MAX_BUFFER_SIZE];
     ssize_t rcv = recv(dSClient, buffer, MAX_BUFFER_SIZE, 0);  // /!\ ici appel
						     // direct de recv
						     // car recvTCP
						     // n'est pas
						     // adapté. Pourquoi ?

      //....
	
      // si pas d'erreurs, j'ai reçu rcv octets. Je dois les écire dans le fichier.
      size_t written = fwrite(buffer, sizeof(char), rcv, file);
      if(written < rcv){
	perror("Serveur : Erreur a l'ecriture du fichier \n");
	//....
	  break; // je sors de la boucle d'écrture/réception.
      }

      contentReceived += rcv;
    }

    // fermeture du fichier à la fin de son écriture ou si erreur s'est produite.
    
    fclose(file);
    printf("Serveur : fin du dialogue avec le client, nombre total d'octets recus : %d,  recus en %d appels a recv \n", write, recv);
    close (dSClient);
    //je passe au client suivant.
  }
  
  close (ds); // atteignable si on sort de la boucle infinie.
  printf("Serveur : je termine\n");
 }}
}







