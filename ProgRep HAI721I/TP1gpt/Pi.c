#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_NEIGHBORS 10 // Maximum number of neighbors for a node

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port_number>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);

    // Initialize an array to store neighbor ports
    int neighbor_ports[MAX_NEIGHBORS];
    int num_neighbors = 0;

    // Create a socket for the node
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("Error creating socket");
        exit(1);
    }

    // Connect to the neighbor's port
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to neighbor");
        exit(1);
    }

    printf("Connected to neighbor on port %d\n", port);

    // Receive the neighbor's port information
    char buffer[10];
    if (recv(socket_fd, buffer, sizeof(buffer), 0) == -1) {
        perror("Error receiving neighbor's port");
        exit(1);
    }
    printf("rcv ok: %s\n", buffer);
    int neighbor_port = atoi(buffer);
    neighbor_ports[num_neighbors++] = neighbor_port;

    // Gérer la réception de la taille de l'anneau avec un nouveau socket
    int ring_size_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (ring_size_socket == -1) {
        perror("Error creating ring size socket");
        exit(1);
    }

    if (connect(ring_size_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting for ring size");
        exit(1);
    }

    char ring_size_info[256];
    if (recv(ring_size_socket, ring_size_info, sizeof(ring_size_info), 0) == -1) {
        perror("Error receiving ring size");
        exit(1);
    }

    int ring_size;
    if (sscanf(ring_size_info, "RingSize:%d", &ring_size) == 1) {
        printf("Node %d: Received ring size: %d\n", port, ring_size);
    }

    // Close the ring size socket
    close(ring_size_socket);

    // Implement your distributed algorithm here

    printf("Node with port %d has finished its task\n", port);

    // Close the neighbor socket
    close(socket_fd);

    return 0;
}
