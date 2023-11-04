
#define CONNECT 1 //reponse serveur
#define FINI 2



struct message {
    int requete;
    int information;
    int information1;
    struct sockaddr_in adresse;
};
