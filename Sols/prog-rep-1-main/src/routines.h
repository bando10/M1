#ifndef _ROUTINE_DEFS_
#define _ROUTINE_DEFS_

// ----------------------------- //
// Déclaration des bibliothèques //
// ----------------------------- //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// -------------------------- //
// Déclaration des constantes //
// -------------------------- //

//Numéro de port de base de l'application
#define LISTEN_PORT_START 9290

//Nombre de secondes au bout duquel les processus commence les demandes de connexion
#define BEGIN_TIMER 10

//Nombre de tentative de connexion maximum autorisée
#define MAX_ATTEMPT_COUNT 3

//Interval de temps maximal (en secondes) avant de redemander une connection
#define MAX_ATTEMPT_INTERVAL 5

//Port par défaut
#define LOCALHOST "127.0.0.1"

// ------------------------------ //
// Déclaration des types utilisés //
// ------------------------------ //

/**
 * Structure noeud du réseau
 */
typedef struct node_t {
    int process_id;                 //identifiant du processus - noeud
    int listen_port_number;         //port d'écoute du processus - noeud
    int listen_socket_id;           //id de la socket d'écoute du processus - noeud
    int *connection_socket_ids;     //tableau des id des sockets permettant de se connecter aux voisins du processus - noeud
    int expected_connection_count;  //nombre de connection attendu
} node_t;

/**
 * Structure des arguments passer à nos threads
 */
typedef struct thread_arg_t {
    node_t *node;
    node_t **neighbours;
    int size;
} thread_arg_t;

/**
 * Structure des arguments passer à nos threads permettant de retenter une nouvelle connexion
 * au bout d'un certains temps.
 */
typedef struct retry_data_t {
    int neighbour_listen_port;
    int neighbour_process_id;
    int neighbour_socket_id;
    int neighbour_index;
    node_t *current_node;
} retry_data_t;

// ------------------------------------------------- //
// Declaration des routines privées de l'application //
// ------------------------------------------------- //

/**
 * routine qui récupére les arguments de la ligne de commande et les parses
 *
 *@param argc nombre d'arguments
 *@param argv tableau d'arguments
 *@param params tableau de stockage des arguments parsés
 *@return params ou -1 en cas d'erreur  
 */
int parse_cli_args(int argc, char *argv[], char *params[]);

/**
 * routine qui lit le fichier pour connaitre tout les voisins d'un processus 
 *
 * @param process_id l'id d'un processus quelconque
 * @param file_path chemin du fichier contenant la description du graphe
 * @param neighbour_count pointeur sur un entier representant le nombre de voisin
 * @param expected_connection_count pointeur sur un entier representant le nombre de connection attendu
 * @return tableau contenant tous les voisins ou NULL en cas d'erreur
 */
node_t **get_neighbour(int process_id, const char *file_path, int *neighbour_count, int *get_expected_connection_count);

/**
 * routine qui crée un noeud du réseau avec l'id passé en argument
 *
 * @param process_id l'id d'un processus quelconque
 * @return un noeud du réseau
 */
node_t *create_node(int process_id);

/**
 * routine qui crée une socket pour le processus avec l'id passé en argument l'attache au
 * numéro de port associé et retourne l'entier permettant d'identifier la socket
 *
 * @param process_id l'id d'un processus quelconque
 * @return renvoie l'id de la socket ou -1 en cas d'erreur
 */
int create_and_bind_socket(int process_id);

/**
 * routine qui crée et retourne une socket TCP
 *
 * @return l'entier permettant d'identifier la socket créée
 */
int create_socket();

/**
 * routine qui crée un tableau constitué des identifiants des socket 
 * permettant au processus de se connecter à ses voisins
 *
 * @param neigbour_count nombre de voisin
 * @param neighbours tableau des voisins
 * @return un tableau ou NULL en cas d'erreur
 */
int *get_connection_socket_ids(node_t **neighbours, int neigbour_count);

/**
 * routine invoquée lors du démarrage du thread permettant d'accepter les connections
 *
 * @param arg passage de la structure thread_arg_t
 */
void *listen_thread_callback(void *arg);

/**
 * routine invoqué lors du démarrage du thread permettant de demander des connections
 *
 * @param arg passage de la structure thread_arg_t
 */
void *connect_thread_callback(void *arg);

/**
 * routine invoqué lors du démarrage du thread permettant de retenter de se connecter à un
 * voisin (au cas où ce dernier ne serait pas encore lancé ou à cause d'un probléme réseau)
 *
 * @param arg passage de la structure thread_arg_t
 */
void *retry_connection_thread(void *arg);

/**
 * routine de gestion d'erreurs
 *
 * @param msg
 */
void handle_error(char* msg);

/**
 * routine de gestion d'erreurs avec arguments
 *
 * @param msg1
 * @param arg
 * @param msg2
 */
void handle_error_var(char* msg1, int arg, char* msg2);

#endif
