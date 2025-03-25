#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    int serverSocket, port;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t len;
    char message[50];

    // Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // Initialize server address structure
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;

    printf("Enter port number: ");
    scanf("%d", &port);
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    printf("\nWaiting for client...\n");

    len = sizeof(clientAddr);
    bzero(&clientAddr, sizeof(clientAddr));

    // Receive message from client
    recvfrom(serverSocket, message, sizeof(message), 0, (struct sockaddr*)&clientAddr, &len);
    printf("\nReceived from client: %s\n", message);

    // Send response
    printf("\nSending response to client...\n");
    sendto(serverSocket, "YOUR MESSAGE RECEIVED.", 22, 0, (struct sockaddr*)&clientAddr, len);

    // Close socket
    close(serverSocket);
    return 0;
}
