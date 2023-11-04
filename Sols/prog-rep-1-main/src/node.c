#include "routines.h"

// ---------------------------- //
// Début du programme principal //
// ---------------------------- //

int main(int argc, char *argv[]) {
    // - Initialisation -

    char *params[2];                        //Contiendra le chemin du fichier ainsi que l'id du processus
    char *file_path;
    int process_id, neighbour_count;        //Id du processus courant et son nombre de voisin
    pthread_t listen_thread, connect_thread;
    node_t **neighbours;                    //tableau des voisins
    node_t *current_node;                   //Noeud courant
    thread_arg_t thread_args;               //Argument des thread

    //Attribut de nos thread permettant de les détacher vu qu'on ne lit pas leur valeurs de retour
    pthread_attr_t attr;
    
    if(pthread_attr_init(&attr) != 0)
        handle_error("\nErreur lors de pthread_attr_init\n");
    if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
        handle_error("\nErreur lors de pthread_attr_setdetachstate\n");

    //Recuperation des arguments depuis la ligne de commande
    if(parse_cli_args(argc, argv, params) == -1) 
        handle_error("\nErreur lors de parse_cli_args\n");

    file_path = params[0];
    process_id = atoi(params[1]);

    // - Récupération des noeuds, de leur voisins ainsi que du nombre de connection attendu -

    current_node = create_node(process_id);

    neighbours = get_neighbour(process_id, file_path, &neighbour_count, &current_node->expected_connection_count);

    thread_args.neighbours = neighbours;
    thread_args.size = neighbour_count;
    thread_args.node = current_node;

    // - Lancement du réseau -

    current_node->listen_socket_id = create_and_bind_socket(current_node->listen_port_number);
    
    if((current_node->connection_socket_ids = get_connection_socket_ids(neighbours, neighbour_count)) == NULL)
        handle_error_var("\nErreur impossible de creer toutes les sockets de connection pour pid = ", 
                          current_node->process_id,
                          ".\n");

    if(current_node->expected_connection_count > 0 && pthread_create(&listen_thread, &attr, listen_thread_callback, &thread_args) != 0)
        handle_error("\nErreur lors de la création du thread d'écoute\n");
    
    if(pthread_create(&connect_thread, &attr, connect_thread_callback, &thread_args) != 0)
        handle_error("\nErreur lors de la création du thread de connection\n");

    if(pthread_attr_destroy(&attr) != 0)
        handle_error("\nErreur lors de la destruction des attributs du thread\n");

    // Cette instruction permet aux threads de ce processus de continuer à
    // s'executer sans pour autant être tué quand le thread principal est terminé
    pthread_exit(NULL);
}

void *listen_thread_callback(void *arg) {

    // - Initialisation -

    thread_arg_t *params = (thread_arg_t *) arg;
    int accepted_connection = 0;
    int new_socket;
    char read_buffer[5]; //buffer de lecture des id des processus connectés

    // - Mise en écoute des demandes de connexion de la socket du processus courant -
    
    listen(params->node->listen_socket_id, params->node->expected_connection_count);

    // - Receptions des connexions -

    fprintf(stdout, "\n[pid = %d] en attente de connexion sur le PORT = %d\n", params->node->process_id, params->node->listen_port_number);

    //Boucle permettant de recevoir toutes les connexions du processus x
    while(accepted_connection < params->node->expected_connection_count){

        if((new_socket = accept(params->node->listen_socket_id, NULL, NULL)) < 0){
            perror("accept");
            pthread_exit(NULL);
        }

        accepted_connection++;

        read(new_socket, read_buffer, sizeof(read_buffer));

        fprintf(stdout, "\n[pid = %d] connexion etablie avec : %s | nombre total de connexion : %d\n", 
                params->node->process_id,read_buffer, accepted_connection);
        
        read_buffer[0] = '\0';
    }

    //Terminaison du thread
    fprintf(stdout, "\n[pid = %d] a fini l'attente de connexion.\n", params->node->process_id);
    pthread_exit(NULL);
}

void *connect_thread_callback(void *arg) {

    // - Initialisation -           

    thread_arg_t *params = (thread_arg_t *) arg;
    struct sockaddr_in neighbour_addr;
    neighbour_addr.sin_family = AF_INET;
    int current_connection_socket_id;
    char str_process_id[5];
    sprintf(str_process_id, "%d", params->node->process_id);

    //Tableau de thread permettant de retenter de se connecter 
    //à un voisins au cas où ce dernier serait injoignable
    pthread_t *retry_threads = (pthread_t *) malloc(params->size * (sizeof(pthread_t)));

    //Les arguments passés aux threads correspondants
    retry_data_t *retry_data = (retry_data_t *) malloc(sizeof(retry_data_t) * params->size);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // - Demande de connections - 

    fprintf(stdout, "\n[pid = %d] première tentative de connexion dans %d sec.\n", 
            params->node->process_id, BEGIN_TIMER);
    sleep(BEGIN_TIMER);

    //On boucle sur les voisins
    for(int i = 0; i < params->size; i++) {
        //Conversion de l'adresse vers un format binaire
        neighbour_addr.sin_port = htons(params->neighbours[i]->listen_port_number);

        if(inet_pton(AF_INET, LOCALHOST, &neighbour_addr.sin_addr) <= 0){
            fprintf(stdout, "\nAdresse IP fournie invalide\n");
            perror("error :");
            pthread_exit(NULL);
        }

        //Socket qui permet de se connecter au bon voisin
        current_connection_socket_id = params->node->connection_socket_ids[i];

        //Si le voisin numéro i n'est pas joignable pour une raison quelconque lors de la premiere tentative
        //de connexion, nous lui créons un thread associé qui va permettre de rententer y fois la 
        //connexion par interval de x secondes
        if(connect(current_connection_socket_id, (struct sockaddr *) &neighbour_addr, sizeof(neighbour_addr)) < 0){

            //Construction des paramétres que nous allons passer au thread permettant de reessayer 
            //la connexion avec le voisin i
            retry_data[i].neighbour_listen_port = params->neighbours[i]->listen_port_number;
            retry_data[i].neighbour_socket_id = current_connection_socket_id;
            retry_data[i].neighbour_process_id = params->neighbours[i]->process_id;
            retry_data[i].neighbour_index = i;
            retry_data[i].current_node = params->node;

            //Creation des threads (pas de pthread_exit car cela peut échoué pour certain voisins mais pas pour d'autre)
            if(pthread_create(&retry_threads[i], &attr, retry_connection_thread, &retry_data[i]) != 0)
                fprintf(stderr, "\n[pid = %d] Erreur lors de la création du thread retry pour le voisin %d\n", params->node->process_id,
                        params->neighbours[i]->process_id);
        } 
        //Connexion réussi : le processus envoie son id au voisin
        else {
            fprintf(stdout, "\n[pid = %d] connecté à %d sur PORT=%d\n", 
                    params->node->process_id,
                    params->neighbours[i]->process_id,
                    params->neighbours[i]->listen_port_number);

            send(current_connection_socket_id, str_process_id, strlen(str_process_id), 0);
        }
    }
    pthread_exit(NULL);
}

void *retry_connection_thread(void *arg) {

    // - Initialisation - 

    int attempt_count = 1, new_socket, result = ECONNREFUSED;
    char str_process_id[5];
    retry_data_t *retry_data = (retry_data_t *)arg;

    struct sockaddr_in neighbour_addr;
    neighbour_addr.sin_family = AF_INET;
    neighbour_addr.sin_port = htons((short)retry_data->neighbour_listen_port);

    if (inet_pton(AF_INET, LOCALHOST, &neighbour_addr.sin_addr) <= 0) {
        printf("\nAdresse IP fournie invalide \n");
        perror("error :");
        pthread_exit(NULL);
    }

    while(attempt_count < MAX_ATTEMPT_COUNT && result != 0) {
        attempt_count++;

        fprintf(stderr, "\n[pid = %d] %d-ieme tentative de joindre %d sur %d dans %d sec.\n", retry_data->current_node->process_id, attempt_count,
                retry_data->neighbour_process_id,
                retry_data->neighbour_listen_port, MAX_ATTEMPT_INTERVAL);
        sleep(MAX_ATTEMPT_INTERVAL);

        new_socket = create_socket();
        retry_data->current_node->connection_socket_ids[retry_data->neighbour_index] = new_socket;

        result = connect(new_socket, (struct sockaddr *) &neighbour_addr, sizeof(neighbour_addr));
    }

    if(attempt_count == MAX_ATTEMPT_COUNT) {
        fprintf(stderr, "\n[pid = %d] Impossible de joindre %d sur %d aprés %d tentatives.\n",
                retry_data->current_node->process_id,
                retry_data->neighbour_process_id,
                retry_data->neighbour_listen_port,
                attempt_count);
    }
    else if(result == 0) {
        fprintf(stderr, "\n[pid = %d] maintenant connecté à %d sur %d aprés %d tentatives.\n",
                retry_data->current_node->process_id,
                retry_data->neighbour_process_id,
                retry_data->neighbour_listen_port,
                attempt_count);

        send(retry_data->current_node->connection_socket_ids[retry_data->neighbour_index], str_process_id,
        strlen(str_process_id), 0);

    }
    pthread_exit(NULL);
}