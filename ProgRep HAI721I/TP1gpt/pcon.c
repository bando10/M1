#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_PIS 4 // Maximum number of Pi processes
#define MAX_NODES 100 // Maximum number of nodes in the graph
#define MAX_NEIGHBORS 10 // Maximum number of neighbors for a node

int graph[MAX_NODES][MAX_NEIGHBORS];

struct PiInfo {
    int pi;
    int tcp_port;
    int udp_port;
};

struct PiInfo pi_info[MAX_PIS];
int num_pis = 0;

void readGraph(const char *filename, int *num_nodes, int *num_edges) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'p' && sscanf(line, "p edge %d %d", num_nodes, num_edges) == 2) {
            // Initialize the graph
            for (int i = 1; i <= *num_nodes; i++) {
                graph[i][0] = 0; // Initialize the number of neighbors to 0
                for (int j = 1; j < MAX_NEIGHBORS; j++) {
                    graph[i][j] = -1; // Initialize neighbor list with -1
                }
            }
        } else if (line[0] == 'e') {
            int node1, node2;
            if (sscanf(line, "e %d %d", &node1, &node2) == 2) {
                if (node1 <= *num_nodes && node2 <= *num_nodes) {
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
        fprintf(stderr, "Usage: %s <port_udp> <graph_file>\n", argv[0]);
        exit(1);
    }

    int udp_port = atoi(argv[1]);
    int udp_socket;

    int num_nodes = 0;
    int num_edges = 0;

    readGraph(argv[2], &num_nodes, &num_edges);
    fprintf(stderr, "readGraph ok. num_nodes: %d, num_edges: %d\n", num_nodes, num_edges);
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(server_addr);

    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket == -1) {
        perror("Error creating UDP socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(udp_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    int reuse = 1;
    if (setsockopt(udp_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        perror("Error setting socket option");
        exit(1);
    }
    if (bind(udp_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding UDP socket");
        exit(1);
    }

    printf("Pconfig is running and listening on UDP port %d...\n", udp_port);

    while (1) {
        struct PiInfo udp_message;
        //memset(&udp_message, 0, sizeof(udp_message));

        if (recvfrom(udp_socket, (struct PiInfo*)&udp_message, sizeof(udp_message), 0, (struct sockaddr *)&client_addr, &len) <=0) {
            perror("Error receiving UDP message");
            continue;
        }
        fprintf(stderr, "Msg de debut de Pi: [%d][UDPPort: %d]\n", udp_message.pi, udp_message.udp_port);



        if (num_pis < MAX_PIS) {
            int new_tcp_port = (num_pis == MAX_PIS - 1) ? pi_info[0].tcp_port : pi_info[num_pis + 1].tcp_port;
            int pi_recu = udp_message.pi;
            int tcp_recu = udp_message.tcp_port;
            int udp_recu = (int)ntohs(client_addr.sin_port);
            struct PiInfo udp_message_recu = {pi_recu, tcp_recu, udp_recu};


            // Prepare a response message for the Pi
            int response = new_tcp_port;
            //snprintf(response, sizeof(response), "%d", new_tcp_port);
            fprintf("new_port: %d\n", new_tcp_port);
            // Send the response back to the Pi
            if (sendto(udp_socket, &response, sizeof(response), 0, (struct sockaddr *)&client_addr, len) == -1) {
                perror("Error sending UDP response");
            }

            // Store Pi's information
            pi_info[num_pis] = udp_message_recu;
//             pi_info[num_pis] = num_pis;
//             pi_info[num_pis].tcp_port = new_tcp_port;

            printf("Pi process discovered: P[%d]: TCP port %d\n[%d Pi] jusqu'a present\n", pi_info[num_pis].pi, pi_info[num_pis].tcp_port, num_pis+1);

            num_pis++;
        }
    }

    close(udp_socket);

    return 0;
}
