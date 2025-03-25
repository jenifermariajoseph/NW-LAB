#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    int clientSocket, port;
    struct sockaddr_in serverAddr;
    socklen_t len;
    char message[50];

    // Create UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // Initialize server address
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;

    printf("Enter port number: ");
    scanf("%d", &port);
    serverAddr.sin_port = htons(port);

    // Flush newline from input buffer before reading message
    getchar();
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    printf("\nSending message to server...\n");
    sendto(clientSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Receive response
    len = sizeof(serverAddr);
    recvfrom(clientSocket, message, sizeof(message), 0, (struct sockaddr*)&serverAddr, &len);
    printf("\nMessage from server: %s\n", message);

    // Close socket
    close(clientSocket);
    return 0;
}
