#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    int client, port=8080;
    struct sockaddr_in serverAddr;
    socklen_t len=sizeof(serverAddr);
    char buffer[1024] = {0};


    // Create UDP socket
    client = socket(AF_INET, SOCK_DGRAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    while(1){
    printf("client: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    sendto(client, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, len);
    if(strcmp(buffer, "exit") == 0){
        break;

    }
    memset(buffer, 0, sizeof(buffer));
    recvfrom(client, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, &len);
    printf("server: %s\n", buffer);
    }
    close(client);
    return 0;
}

