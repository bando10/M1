#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include "commons.h"

int main( int argc,char* argv[]){

    //Verification arguments: 
    if(argc!=4){
        printf("utilisation : %s ip_serv port_serv num_port_client \n",argv[0]);
        exit(1);
    }

<<<<<<< HEAD
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
char m[1000];
   printf("Message a envoyer: \n");
   fgets(m, sizeof(m), stdin);
   ssize_t res = send(ds, &m, strlen(m) * sizeof(int), 0);
   printf("Client : nombre d'octets envoyes : %d \n", (int)res);

=======
    //Création socket client: 
    int client_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(client_sock==-1){
        perror("socket failed");
        exit(1);
    }
    printf("client: socket created \n");

    //nommage socket client:
    struct sockaddr_in addr_client;
    addr_client.sin_family=AF_INET;
    addr_client.sin_addr.s_addr=INADDR_ANY;
    addr_client.sin_port=htons(atol(argv[3]));

    int res=bind(client_sock,(struct sockaddr*)&addr_client,sizeof(addr_client));
    if(res==-1){
        perror("bind failed");
        exit(1);
    }
    printf("client: bind done \n");



    //Designation socket serveur: 
    struct sockaddr_in addr_serv;
    addr_serv.sin_family=AF_INET;
    addr_serv.sin_addr.s_addr=inet_addr(argv[1]);
    addr_serv.sin_port=htons(atol(argv[2]));
    socklen_t lgA=sizeof(addr_serv);

    //connect
    res=connect(client_sock,(struct sockaddr*)&addr_serv,lgA);
    if(res==-1){
        perror("connect failed");
        exit(1);
    }
    printf("client: connected ! \n");

    //Envoie de messages:
    char message[150];
    printf("Veuillez saisir un message \n");
    res=scanf("%[^\n]",message);
    if(res==-1){
        perror("scanf failed");
        exit(1);
    }

    printf("Message to send: %s longeur: %ld \n",message,strlen(message));
    res=sendtcp(client_sock,message,strlen(message)+1);
    if(res==-1){
        perror("send failed");
        exit(1);
    }else if(res==0){
        perror("sendfailed socket closed \n");
        exit(1);
    }else if(res!=1){
    perror("messages uncomplete \n");}

    //Reception message:
    char msg[100];
    res=recvtcp(client_sock,msg,sizeof(msg));
     if(res==-1){
        perror("recv failed");
        exit(1);
    }else if(res==0){
        perror("recv failed socket closed");
        exit(1);
    }
    printf("serv: message reçu: \n %s \n",msg);
>>>>>>> 967a785ecd84175a4c65dc29ca93e9c66ac24522


    printf(" client: Message envoyé, %d octets pris en compte \n",res);


    //Fermeture socket
    res=close(client_sock);
    if(res==-1){
        perror("close failed");
        exit(1);
    }
    printf("client socoket closed succesfully");

}