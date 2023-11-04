#include "routines.h"

// ------------------------------------------------ //
// Définition des routines privées de l'application //
// ------------------------------------------------ //

int parse_cli_args(int argc, char *argv[], char *params[]) {
    int fflag = 0, pflag = 0, option;
    opterr = 0; //Pas de message d'erreur automatique

    while((option = getopt(argc, argv, "f:p:")) != -1)
        switch(option) {
            case 'f':
                params[0] = optarg;
                fflag = 1;
                break;
            case 'p':
                params[1] = optarg;
                pflag = 1;
                break;
            case '?':
                fprintf(stderr, "option %c non prise en compte", optopt);
                break;
        }

    if(!fflag || !pflag)
        handle_error("\nAttention utilisation : node -f <file_path> -p <process_id>\n");
  
    return 0;
}

node_t *create_node(int process_id) {
    node_t *node = (node_t *) malloc(sizeof(node_t));
    if(node == NULL) handle_error("error malloc : create_node\n");

    node->process_id = process_id;
    node->listen_port_number = LISTEN_PORT_START + process_id;
    node->listen_socket_id = 0;
    node->connection_socket_ids = NULL;
    node->expected_connection_count = 0;

    return node;
}

node_t **get_neighbour(int process_id, const char *file_path, int *neighbour_count, int *expected_connection_count) {
    FILE *file = fopen(file_path, "r");
    char line_tmp[200], line[200];
    char *tokens = NULL;
    char delim[] = " ";
    int token_position = 0, size = 0, cursor = 0, expected_connection = 0;

    char prefix[15];
    sprintf(prefix, "e %d ", process_id);

    node_t **neighbours = (node_t **)malloc(sizeof(node_t *));

    if(neighbour_count == NULL) neighbour_count = (int *)malloc(sizeof(int));

    if(!file) handle_error("\nImpossible d'ouvrir le fichier !\n");

    while((line_tmp[cursor] = (char)fgetc(file)) != EOF) {

        if(line_tmp[cursor] == '\n') {
            token_position = 0;
            strcpy(line, line_tmp);
            tokens = strtok(line_tmp, delim);

            while(tokens != NULL) {

                tokens = strtok(NULL, " ");
                token_position++;
                if(token_position == 2) {
                    if(strncmp(prefix, line, strlen(prefix)) == 0) {
                        size++;
                        if(size == 1)
                            neighbours[0] = create_node(atoi(tokens));
                        else {
                            neighbours = (node_t **)realloc(neighbours, size * sizeof(node_t *));
                            neighbours[size - 1] = create_node(atoi(tokens));
                        }
                    } 
                    else if(strncmp("e", line_tmp, 1) == 0 && atoi(tokens) == process_id)
                        expected_connection ++; 
                } 

            }
            line_tmp[cursor + 1] = '\0';
            cursor = 0;
        } 
        else cursor++;
    }

    *neighbour_count = size;
    *expected_connection_count = expected_connection;

    if(fclose(file) == EOF) handle_error("Erreur lors de la fermeture du fichier\n");

    return neighbours;
}

int create_and_bind_socket(int port_number) {
    int socket_id = create_socket();

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_number);

    // affectation de l'adresse a la socket
    if (bind(socket_id, (struct sockaddr *)&address, sizeof(address)) < 0)
        handle_error("\nErreur : attachement du socket au port.\n");

    return socket_id;
}

int *get_connection_socket_ids(node_t **neighbours, int neighbour_count) {
    int *socket_ids = (int *) malloc(neighbour_count * sizeof(int));

    for(int i = 0; i < neighbour_count; i++)
        if((socket_ids[i] = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            fprintf(stderr, "erreur lors de la creation de la socket de connection pour %d\n",
                    neighbours[i]->process_id);
            return NULL;
        }

    return socket_ids;
}

int create_socket() {
    int socket_id, opt = 1;

    if((socket_id = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        handle_error("\n Impossible de creer la socket pour \n");

    // Positionnement d'une option sur la socket permettant de réutiliser le port
    // cette option permet de relancer un serveur TCP sans obtenir l'erreur "address already in use"
    if(setsockopt(socket_id, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
        handle_error("\nImpossible de positionner l'option SO_REUSEPORT\n");

    return socket_id;
}

void handle_error(char *msg) {
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}

void handle_error_var(char *msg1, int arg, char *msg2) {
    fprintf(stderr, "%s%d%s", msg1, arg, msg2);
    exit(EXIT_FAILURE);
}