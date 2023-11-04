#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct PiInfo {
    int pi;
    int tcp_port;
    int udp_port;
};
// Variables for ring size calculation
int ring_size = 1;
int message_received = 0;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <pconfig_udp_port>  <port_tcp> <ring_index>\n", argv[0]);
        exit(1);
    }

    int pconfig_udp_port = atoi(argv[1]);
    int ring_index = atoi(argv[3]);
    int tcp_port = atoi(argv[2]);

    // Create a socket for UDP communication
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket == -1) {
        perror("Error creating UDP socket");
        exit(1);
    }

    // Register the Pi with Pconfig
    struct PiInfo udp_message = {ring_index, tcp_port, pconfig_udp_port};
    struct sockaddr_in pconfig_addr, neighbor_addr;

    pconfig_addr.sin_family = AF_INET;
    pconfig_addr.sin_port = htons(pconfig_udp_port);
    pconfig_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to the actual IP address if needed

    if (sendto(udp_socket, &udp_message, sizeof(udp_message), 0, (struct sockaddr *)&pconfig_addr, sizeof(pconfig_addr)) == -1) {
        perror("Error sending UDP registration message to Pconfig");
        close(udp_socket);
        exit(1);
    }

    printf("Pi with ring index %d is running and listening on UDP port %d...\n", ring_index, pconfig_udp_port);

    // Receive the neighbor's TCP port from Pconfig
    int udp_response;
    socklen_t len = sizeof(neighbor_addr);

    if (recvfrom(udp_socket, &udp_response, sizeof(udp_response), 0, (struct sockaddr *)&neighbor_addr, &len) == -1) {
        perror("Error receiving UDP response from Pconfig");
        close(udp_socket);
        exit(1);
    }

    int neighbor_tcp_port = udp_response;
    close(udp_socket);

    printf("Received neighbor's TCP port: %d\n", neighbor_tcp_port);

    // Create a socket for TCP communication
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket == -1) {
        perror("Error creating TCP socket");
        exit(1);
    }

    // Connect to the neighbor's TCP port
    neighbor_addr.sin_family = AF_INET;
    neighbor_addr.sin_port = htons(neighbor_tcp_port);
    neighbor_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to the actual IP address if needed

    // Bind the TCP socket to the specified port
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(tcp_port);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(tcp_socket, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {
        perror("Error binding TCP socket");
        close(tcp_socket);
        exit(1);
    }

    // Listen for incoming connections
    if (listen(tcp_socket, 1) == -1) {
        perror("Error listening on TCP socket");
        close(tcp_socket);
        exit(1);
    }
 // Accept incoming connections from the predecessor in the ring
int predecessor_socket;
struct sockaddr_in predecessor_addr;
socklen_t predecessor_len = sizeof(predecessor_addr);

predecessor_socket = accept(tcp_socket, (struct sockaddr *)&predecessor_addr, &predecessor_len);

if (predecessor_socket == -1) {
    perror("Error accepting incoming connection from predecessor");
    close(tcp_socket);
    exit(1);
}

printf("Accepted connection from predecessor on TCP port %d\n", ntohs(predecessor_addr.sin_port));

// Connect to the neighbor on the other end of the ring
if (connect(tcp_socket, (struct sockaddr *)&neighbor_addr, sizeof(neighbor_addr)) == -1) {
    perror("Error connecting to neighbor");
    exit(1);
}

printf("Connected to the neighbor on TCP port %d\n", neighbor_tcp_port);

// Receive messages from the predecessor
char tcp_response[256];

if (recv(predecessor_socket, tcp_response, sizeof(tcp_response), 0) == -1) {
    perror("Error receiving TCP response");
    close(tcp_socket);
    exit(1);
}

if (strstr(tcp_response, "StartRingSizeCalculation:") != NULL) {
    // This is the initial message to start the calculation
    int origin_pi;
    if (sscanf(tcp_response, "StartRingSizeCalculation:%d", &origin_pi) == 1) {
        if (origin_pi != udp_message.pi) {
            char forward_message[256];
            snprintf(forward_message, sizeof(forward_message), "ForwardRingSizeCalculation:%d:%d", origin_pi, udp_message.pi);

            if (send(predecessor_socket, forward_message, strlen(forward_message), 0) == -1) {
                perror("Error forwarding TCP message");
                close(tcp_socket);
                exit(1);
            }
        }
    }
} else if (strstr(tcp_response, "ForwardRingSizeCalculation:") != NULL) {
    // This is a forwarded message, pass it on
    int origin_pi, current_pi;
    if (sscanf(tcp_response, "ForwardRingSizeCalculation:%d:%d", &origin_pi, &current_pi) == 2) {
        if (current_pi != udp_message.pi && current_pi != origin_pi) {
            char forward_message[256];
            snprintf(forward_message, sizeof(forward_message), "ForwardRingSizeCalculation:%d:%d", origin_pi, current_pi);

            if (send(predecessor_socket, forward_message, strlen(forward_message), 0) == -1) {
                perror("Error forwarding TCP message");
                close(tcp_socket);
                exit(1);
            }
        } else if (current_pi == udp_message.pi) {
            // This is the message returning to the original Pi
            message_received++;
            if (message_received == origin_pi) {
                // All Pi processes have received the message; calculate ring size
                ring_size = origin_pi;
                printf("Ring size: %d\n", ring_size);
            }
        }
    }
}

close(predecessor_socket);
close(tcp_socket);

    return 0;
}
