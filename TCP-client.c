#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>

int main() {
    int client_socket, port_number;
    struct sockaddr_in server_address;
    socklen_t address_length;
    char message[50];

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize server address structure
    bzero((char*)&server_address, sizeof(server_address));
    address_length = sizeof(server_address);
    server_address.sin_family = AF_INET;

    // Get port number from user
    printf("Enter the port number: ");
    scanf("%d", &port_number);
    server_address.sin_port = htons(port_number);

    // Attempt connection to the server
    printf("\nTrying to connect to the server...\n");
    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    printf("\nConnected to the server.\n");

    // Send message to the server
    printf("\nSending message to server...\n");
    send(client_socket, "HI, I AM CLIENT...", sizeof("HI, I AM CLIENT..."), 0);

    // Receive response from server
    printf("\nReceiving message from server...\n");
    recv(client_socket, message, sizeof(message), 0);
    
    // Print received message
    printf("\nMessage received: %s\n", message);

    // Close the socket
    close(client_socket);
}
