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
