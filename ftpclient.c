#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5035
#define BUFFER 60

int main() {
    int clientSocket, bytesRead;
    struct sockaddr_in serverAddr;
    char fileName[BUFFER], fileContent[BUFFER];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
    serverAddr.sin_port = htons(PORT);

    // Connect to server
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Get filename from user
    printf("\nEnter the source file name: ");
    scanf("%s", fileName);

    // Send filename to server
    write(clientSocket, fileName, BUFFER);

    // Receive and display file content
    while ((bytesRead = read(clientSocket, fileContent, BUFFER)) > 0) {
        printf("%s", fileContent);
    }

    close(clientSocket);
    return 0;
}
