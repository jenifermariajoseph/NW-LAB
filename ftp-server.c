#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 5035
#define BUFFER 4096
#define FILENAME 60

int main() {
    int serverSocket, clientSocket;
    socklen_t clientLength;
    struct sockaddr_in serverAddr, clientAddr;
    char fileName[FILENAME], buffer[BUFFER];
    FILE *file;

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind socket
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("\nServer is bound to port %d", PORT);

    // Listen for incoming connections
    listen(serverSocket, 5);
    printf("\nWaiting for client connection...");

    // Accept client connection
    clientLength = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLength);
    close(serverSocket);

    // Receive filename from client
    read(clientSocket, fileName, FILENAME);
    printf("\nClient requested file: %s\n", fileName);

    // Open the requested file
    file = fopen(fileName, "r");

    // Send file content
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        write(clientSocket, buffer, strlen(buffer));
    }

    fclose(file);
    printf("\nFile transfer complete.\n");

    close(clientSocket);
    return 0;
}
