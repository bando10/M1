#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>

ssize_t sendtcp(int socket, void* msg, int lg){
    int cpt=0;
    int i=0;
    //Premier send de la longueur du message:
    int s=send(socket,&lg,sizeof(lg),0);
    if(s==-1){
        return -1;
    }else if(s==0){
        return 0;
    }
    printf("taille du message à envoyé: %d \n",lg);
    //Send du message:
    while(cpt!=lg){
        s=send(socket,msg+cpt,lg-cpt,0);
        if(s==-1){
            return -1;
        }else if(s==0){
            return 0;
        }
        cpt+=s;
        i++;
        printf("%d tours de boucles pour sendtcp \n",i);
    }
    return 1;
}


ssize_t recvtcp(int socket, void* msg, int max_lg){
    int cpt=0;
    int i=0;
    int lg;
    //Premier recv taille message;
    int s=recv(socket,&lg,sizeof(lg),0);
     if(s==-1){
            return -1;
        }else if(s==0){
            return 0;
        }
    printf("taille du message attendu :%d \n",lg);
    //Recv du message
    while(cpt!=lg && cpt<max_lg){
        s=recv(socket,msg+cpt,max_lg,0);
        if(s==-1){
            return -1;
        }else if(s==0){
            return 0;
        }
        cpt+=s;
        i++;
        printf("%d tours de boucles pour recvtcp \n",i);
    }
    return 1;
}