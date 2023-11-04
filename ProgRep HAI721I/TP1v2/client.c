#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "fcts.c"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        if (argc != 3)
        {
            // todo Changer nb arg pour port client et ip client
            printf("Utilisation : %s  ip_serveur port_serveur ip_client port_client \n ip_client initialisé si NULL\n port_client initialisé si NULL \n", argv[0]);
            exit(1);
        }
    }

    int nbClientConnecte = 0;

    int ds = socket(PF_INET, SOCK_STREAM, 0);
    if (ds == -1)
    {
        perror("Client : Problème d'initialisation de socket");
        exit(1);
    }

    printf("Client : creation de la socket réussie \n");
    // adresse de la socket client
    struct sockaddr_in ad;
    ad.sin_family = AF_INET;
    // ARGC 5
    if (argc == 5)
    {
        inet_pton(AF_INET, argv[3], &(ad.sin_addr));
        ad.sin_port = htons((short)atoi(argv[4]));
    }
    else
    { // argc 3
        ad.sin_addr.s_addr = INADDR_ANY;
        ad.sin_port = 0;
    }
    int res;
    res = bind(ds, (struct sockaddr *)&ad, sizeof(ad));
    if (res == -1)
    {
        printf("Client: Pb socket\n");
    }

    printf("Client: bind socket ok \n");

    // connexion
    // adresse a laquel on bind (serveur)
    struct sockaddr_in adserveur;
    adserveur.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(adserveur.sin_addr));
    adserveur.sin_port = htons((short)atoi(argv[2]));
    socklen_t lg_Adr = sizeof(struct sockaddr_in);

    int resultConnexion = connect(ds, (struct sockaddr *)&adserveur, lg_Adr);

    if (resultConnexion == -1)
    {
        perror("Client : Problème de connexion");
        exit(1);
    }
    printf("Client: connexion ok \n");

    struct message Message;

    // socket ecoute

    int dsListen = socket(PF_INET, SOCK_STREAM, 0);
    int option = 1;
    setsockopt(dsListen, SOL_SOCKET, SO_REUSEADDR, (char *)&option, sizeof(option));
    int resBind = bind(dsListen, (struct sockaddr *)&ad, lg_Adr);
    if (resBind == -1)
    {
        perror("Problème de bind dslisten");
        exit(1);
    }

    int dsvoisin = socket(PF_INET, SOCK_STREAM, 0);
    fd_set set, settmp;
    FD_ZERO(&set);
    FD_SET(dsListen, &set);
    FD_SET(ds, &set);
    int max = (dsListen > ds) ? dsListen : ds;

    struct sockaddr_in infos;
    socklen_t lg_info = sizeof(infos);
    getsockname(dsListen, (struct sockaddr *)&infos, &lg_info); // recup port
    int infoport = infos.sin_port;
    getsockname(ds, (struct sockaddr *)&infos, &lg_info); // recup ip
    infos.sin_port = infoport;
    Message.adresse = infos;
    send(ds, &Message, sizeof(Message), 0);
    int reception = recv(ds, &Message, sizeof(Message), 0); // premier mess serv
    if (reception < 0)
    {
        perror("Client : probleme de reception du message du serveur \n ");
    }
    int nbVoisins = Message.information;
    int nbRecois = Message.information1;
    int socketlist[nbVoisins];
    FILE* logClient = NULL;
    char nomFichier[500] ="";
    strcat(nomFichier,"log/");

    char numPort[100];
    sprintf(numPort,"%d",infoport);
    strcat(nomFichier,numPort);
    printf("num Port : %s \n", numPort);
    strcat(nomFichier,".txt");
    printf("Nom du fichier %s \n", nomFichier);

    logClient = fopen(nomFichier,"w");
    if(logClient !=NULL){
        fputs("Fichier crée \n", logClient);
        printf("Fichier OK");
    }  
    printf("jai %d voisins et %d connection a faire\n",nbVoisins,nbRecois);
    listen(dsListen, nbRecois);
    int nb = 0;
    while (1)
    {

        settmp = set;

        int resSelect = select(max + 1, &settmp, NULL, NULL, NULL);
        if (resSelect == -1)
        {
            perror("Client : Probleme de select");
            exit(1);
        }
        for (int df = 2; df <= max; df++)
        {
            if (!FD_ISSET(df, &settmp))
            {
                continue;
            }

            if (df == dsListen)
            {
                printf("reçoit un voisin\n");
                int dsc = accept(dsListen, NULL, NULL);
                if (dsc == -1)
                {
                    perror("problème d'accepte dsListen \n");
                    exit(1);
                }
                FD_SET(dsc, &set);
                if (max < dsc)
                    max = dsc;
                printf("Client : Accepte dsListen ok");
                socketlist[nbClientConnecte] = dsc;
                nbClientConnecte++;
                if (max < dsListen)
                {
                    max = dsListen;
                }
                continue;
            }
            if (df == ds)
            {
                printf("reçoit un message du serveur\n");
                int reception = recv(ds, &Message, sizeof(Message), 0);
               
                if (reception < 0)
                {
                    perror("Client : probleme de reception du message du serveur \n ");
                }
                if (reception == 0)
                {
                    close(ds);
                    FD_CLR(ds, &set);
                    continue;
                }
                if (Message.requete == CONNECT)
                {
                    fprintf(logClient, "message du serv %s  :  %d \n", inet_ntoa(Message.adresse.sin_addr), Message.adresse.sin_port);
                    printf("message du serv %s  :  %d \n", inet_ntoa(Message.adresse.sin_addr), Message.adresse.sin_port);
                    int dsvoisin = socket(PF_INET, SOCK_STREAM, 0);
                    int resultConnexion = connect(dsvoisin, (struct sockaddr *)&Message.adresse, lg_Adr);
                    if (resultConnexion == -1)
                    {
                        perror("Client : Problème de connexion voisin");
                        exit(1);
                    }
                    socketlist[nbClientConnecte] = dsvoisin;
                    nbClientConnecte++;
                    // FD_SET(dsvoisin, &set);
                    nb++;
                    continue;
                }
            }
        }
        if(nbVoisins == nbClientConnecte){
            break;
        }
        
    }
    fprintf(logClient,"j ai %d connexions \n", nbClientConnecte);
    printf("j ai %d connexions \n", nbClientConnecte);




    fclose(logClient);
    close(ds);
    for (int i = 0; i < nbVoisins; i++)
    {
        close(socketlist[i]);
    }
    return 0;
}
 
