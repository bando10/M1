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

    int max_size = 1000;
    int nbsommet = 4;
    char *ligne = NULL;
    ssize_t read;
    ssize_t len = 0;

    if (argc != 4)
    {
        printf("utilisation : %s port_serveur ip_serveur nomFichier \n", argv[0]);
        exit(1);
    }

    FILE *fichier = fopen(argv[3], "r");
    if (fichier == NULL)
    {
        perror("echec a la lecture du graphe");
    }

    // On va ignorer les ligne avant les informations
    while (((read = getline(&ligne, &len, fichier)) != -1) && (ligne[0] != 'p'))
    {
    }
    char buflecture[50];
    sscanf(ligne, "p %[^ ] %i",(char*)& buflecture, &nbsommet);

    // tableau de voisins
    int **voisins = (int **)malloc(nbsommet * sizeof(int *));

    for (int i = 0; i < nbsommet; i++)
    {
        voisins[i] = (int *)malloc(nbsommet * sizeof(int));
    }

    // matrice des liaisons init a 0
    for (int i = 0; i < nbsommet; i++)
    {
        for (int j = 0; j < nbsommet; j++)
        {
            voisins[i][j] = 0;
        }
    }

    // on recupere les liaisons
    while ((read = getline(&ligne, &len, fichier) != -1))
    {

        printf("%s\n", ligne);
        int i = 0;
        int j = 0;
        sscanf(ligne, "e %i %i", &i, &j);
        printf("%i %i \n", i,j);
        //  les intersections ligne colone des voisins devient 1 envoyeur 2 receveur
        voisins[i - 1][j - 1] = 1;
        voisins[j - 1][i - 1] = 2;
    }
    fclose(fichier);
    printf("DEBUT \n");

    int ds = socket(PF_INET, SOCK_STREAM, 0);
    if (ds == 0)
    {
        perror("Serveur : pb creation socket :");
        exit(1);
    }

    printf("apres creation socket \n");
    struct sockaddr_in adress;
    adress.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(adress.sin_addr));
    adress.sin_port = htons((short)atoi(argv[2]));

    printf("bind socket: \n");
    // bind de la socket
    int resultBind;
    resultBind = bind(ds, (struct sockaddr *)&adress, sizeof(adress));
    if (resultBind == -1)
    {
        perror("Problème de création de socket (bind)\n");
        exit(1);
    }
    printf("bind reussis\n");
    // ecoute de la socket
    int resultListen;
    resultListen = listen(ds, nbsommet);
    if (resultListen == -1)
    {
        perror("Problème de mise en écoute\n");
        exit(1);
    }
    printf("listen reussis\n");
    struct sockaddr_in addrclient;
    socklen_t lgAdr = sizeof(addrclient);

    // tableau des adresses et ports des noeuds
    struct sockaddr_in connexions[nbsommet];
    int nbconnecte = 0;

    int iclient = 0; // var pour remplir le tableau socket client
    int socketclients[nbsommet];
    while (nbconnecte < nbsommet)
    {
        // accept la connexion
        int dsClient = accept(ds, (struct sockaddr *)&addrclient, &lgAdr);
        socketclients[iclient] = dsClient;
        char str[INET_ADDRSTRLEN];
        if (dsClient == -1)
        {
            perror("Problème d'acceptation de la connexion");
            exit(1);
        }
        struct message MessageAdresseSocketClient;
        int reception = recv(dsClient, &MessageAdresseSocketClient, sizeof(MessageAdresseSocketClient), 0);
        if (reception == -1)
        {
            perror("Problème d'envoie du message \n");
            exit(1);
        }

        // ajout au tableau de connexions
        connexions[nbconnecte] = MessageAdresseSocketClient.adresse; // adresse

        nbconnecte++;
        printf("nb de clients écouté : %d\n", nbconnecte);
        iclient++;
    }

    for (int i = 0; i < nbsommet; i++)
    {
        int nbvoisins = 0;
        int nbenvoie = 0;
        int nbrecois = 0;
        // parcour tab voisin pour avoir le nbvoisins de i
        for (int k = 0; k < nbsommet; k++)
        {
            if (voisins[k][i] == 1)
            {
                nbenvoie++;
            }
            else if (voisins[k][i] == 2)
            {
                nbrecois++;
            }
        }

        struct message Message;
        Message.information = nbvoisins;

        struct message Messageintro;
        Messageintro.information = nbenvoie + nbrecois;
        Messageintro.information1 = nbrecois;
        send(socketclients[i], &Messageintro, sizeof(Messageintro), 0);
        printf("nombre de voisins %i \n", Messageintro.information);
        printf("nombre recois  %i \n", Messageintro.information1);

        for (int n = 0; n < nbsommet; n++) // envoie addr 1 par 1
        {
            if (voisins[n][i] == 2)
            {
                Message.requete = CONNECT;
                Message.adresse = connexions[n];
                send(socketclients[i], &Message, sizeof(Message), 0);
                printf("envoie quand requête == CONNECT %s  :  %d \n", inet_ntoa(Message.adresse.sin_addr), Message.adresse.sin_port);
            }
        }

       
    }
 struct message messageFin;
    for (int n = 0; n < nbsommet; n++) // envoie fini a chaque client
    {
        messageFin.requete = FINI;
        send(socketclients[n], &messageFin, sizeof(messageFin), 0);
    }

    for (int i = 0; i < nbsommet; i++)
    {
        close(socketclients[i]);
    }

    close(ds);
    return 0;
} 
