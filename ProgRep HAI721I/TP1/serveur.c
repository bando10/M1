#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include "commons.h"

<<<<<<< HEAD
int main(int argc, char *argv[]) {
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
    res = recv(dSClient, &m, sizeof(m), 0);
    if(res ==-1){
        perror("Serveur : erreur a la reception ");
        exit(1);
    } /* else if (res==0){
    perror("socket fermee\n");
    exit(1); */
    m[(int)res]="\0";
    printf("Serveur : message recu de la part de : %s:%d \n", inet_ntoa(sockClient.sin_addr), ntohs(sockClient.sin_port));
    printf("Serveur : message reçu : %s \n", m);}

    /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
    close(ds);
    printf("Serveur : je termine\n");
  return 0;
}
=======
int main( int argc,char* argv[]){

    //Verification arguments: 
    if(argc!=2){
        printf("utilisation : %s num_port_serv \n",argv[0]);
        exit(1);
    }

    //Création socket serveur: 
    int serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock==-1){
        perror("socket failed");
        exit(1);
    }
    printf("serv: socket created \n");

    //nommage socket serveur:
    struct sockaddr_in addr_serv;
    addr_serv.sin_family=AF_INET;
    addr_serv.sin_addr.s_addr=INADDR_ANY;
    addr_serv.sin_port=htons(atol(argv[1]));

    int res=bind(serv_sock,(struct sockaddr*)&addr_serv,sizeof(addr_serv));
    if(res==-1){
        perror("bind failed");
        exit(1);
    }
    printf("serv: bind done \n");

    //listen
    while(1){
    res=listen(serv_sock,10);
    if(res==-1){
        perror("listen failed");
        exit(1);
    }
    printf("serv: listening on port %s ... \n",argv[1]);

    //accept
    struct sockaddr_in addr_client;
    socklen_t lgA=sizeof(addr_client);
    int client_sock=accept(serv_sock,(struct sockaddr*)&addr_client,&lgA);
    if(client_sock==-1){
        perror("accept failed");
        exit(1);
    }
    printf("serv: client accepted \n");


    //Reception message: 
    char message[150];

    res=recvtcp(client_sock,message,sizeof(message));
    if(res==-1){
        perror("recv failed");
        exit(1);
    }else if(res==0){
        perror("recv failed socket closed");
        exit(1);
    }
    printf("serv: message reçu: \n %s \n",message);

    //Renvoie d'une réponse: 
    char *msg="SAH JE SUIS SERVEUR JAI RECU";
    res=sendtcp(client_sock,msg,strlen(msg)+1);
    if(res==-1){
        perror("sendfailed");
        exit(1);
    }else if(res==0){
        perror("send failed socket closed \n");
        exit(1);
    }
    printf("serv: message sended \n");
    }
    //Fermeture socket
    res=close(serv_sock);
     if(res==-1){
        perror("close failed");
        exit(1);
    }
    printf("serv: socket closed succesfully \n");


}
>>>>>>> 967a785ecd84175a4c65dc29ca93e9c66ac24522
