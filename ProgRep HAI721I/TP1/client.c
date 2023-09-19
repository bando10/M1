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


    printf(" client: Message envoyé, %d octets pris en compte \n",res);


    //Fermeture socket
    res=close(client_sock);
    if(res==-1){
        perror("close failed");
        exit(1);
    }
    printf("client socoket closed succesfully");

}