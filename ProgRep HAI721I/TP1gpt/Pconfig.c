#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_NODES 100 // Maximum number of nodes in the graph
#define MAX_NEIGHBORS 10 // Maximum number of neighbors for a node


int graph[MAX_NODES][MAX_NEIGHBORS]; // Adjacency matrix for the graph


void readGraph(const char *filename, int *num_nodes, int *num_edges) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'p' && sscanf(line, "p edge %d %d", &num_nodes, &num_edges) == 2) {
            // Initialize the graph
            for (int i = 1; i <= num_nodes; i++) {
                graph[i][0] = 0; // Initialize the number of neighbors to 0
                for (int j = 1; j < MAX_NEIGHBORS; j++) {
                    graph[i][j] = -1; // Initialize neighbor list with -1
                }
            }
        } else if (line[0] == 'e') {
            int node1, node2;
            if (sscanf(line, "e %d %d", &node1, &node2) == 2) {
                if (node1 <= num_nodes && node2 <= num_nodes) {
                    graph[node1][graph[node1][0] + 1] = node2;
                    graph[node1][0] += 1;

                    graph[node2][graph[node2][0] + 1] = node1;
                    graph[node2][0] += 1;
                }
            }
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <graph_file>\n", argv[0]);
        exit(1);
    }

    int num_nodes = 0;
    int num_edges = 0;

    readGraph(argv[2], &num_nodes, &num_edges);
    int neighbor_sockets[MAX_NODES];

    // Create and bind sockets for each node based on graph
   // Create a socket for Pconfig to listen for incoming connections
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(1);
    }


    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons((short)atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    int reuse = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        perror("Error setting socket option");
        exit(1);
    }

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    printf("Listening on port %d\n",(short)atoi(argv[1]));
    listen(server_socket, 10); // Listen for one incoming connection
    printf("listen ok\n");
    // Accept incoming connection from a Pi process
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);

    if (new_socket < 0) {
        perror("Error accepting connection from Pi");
        exit(1);
    }
    printf("accept ok\n");
    // Receive information from Pi about its existence and neighbors
    char pi_info[256];
    memset(pi_info, 0, sizeof(pi_info));

    if (recv(new_socket, pi_info, sizeof(pi_info), 0) == -1) {
        perror("Error receiving Pi information");
        exit(1);
    }
    printf("rcv info ok: %s\n", pi_info);
// Parse the Pi information and establish connections with neighbors
int neighbor_port, node;
if (sscanf(pi_info, "Pi%d,Neighbor:%d", &node, &neighbor_port) == 2) {
    // Create a socket to connect to the next Pi
    int neighbor_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (neighbor_socket == -1) {
        perror("Error creating socket for neighbor");
        exit(1);
    }

    struct sockaddr_in neighbor_addr;
    neighbor_addr.sin_family = AF_INET;
    neighbor_addr.sin_port = htons(neighbor_port);
    neighbor_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to the actual IP address if needed

    if (connect(neighbor_socket, (struct sockaddr *)&neighbor_addr, sizeof(neighbor_addr)) == -1) {
        perror("Error connecting to neighbor");
        exit(1);
    }
    printf("connwct neighbor ok\n");
    // Code pour calculer la taille de l'anneau
    int ring_size = 0;
    int first_node = -1;
    int current_node = 1;
    int visited[MAX_NODES] = {0};

    for (int i = 1; i <= num_nodes; i++) {
        if (i != node) {
            neighbor_sockets[i] = socket(AF_INET, SOCK_STREAM, 0);
            if (neighbor_sockets[i] == -1) {
                perror("Error creating socket for neighbor");
                exit(1);
            }
        }
    }


    while (current_node != -1 && !visited[current_node]) {
        visited[current_node] = 1;
        ring_size++;
        if (first_node == -1) {
            first_node = current_node;
        }
        current_node = graph[current_node][1]; // Suivant le voisin
    }

    if (current_node == first_node && ring_size > 0) {
        // C'est un anneau
        printf("Ring size: %d\n", ring_size);
        // Envoyer la taille de l'anneau à tous les nœuds
        char ring_size_info[256];
        snprintf(ring_size_info, sizeof(ring_size_info), "RingSize:%d", ring_size);

        for (int i = 1; i <= num_nodes; i++) {
            if (i != node) {
                send(neighbor_sockets[i], ring_size_info, strlen(ring_size_info), 0);
                close(neighbor_sockets[i]);
            }
        }
    }


    // Close the socket for neighbor

}
    close(server_socket);

    return 0;
}
