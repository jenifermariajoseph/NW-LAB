#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#define PORT 8080

int main() {
    int server;
    struct sockaddr_in servaddr, cliAddr;
    socklen_t clen=sizeof(cliAddr);
    char buffer[1024] = {0};

    // Create UDP socket
    server = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(server, (struct sockaddr*)&servaddr, sizeof(servaddr));

    while(1){
        memset(buffer,0,sizeof(buffer));
        recvfrom(server, buffer, sizeof(buffer),0, (struct sockaddr*)&cliAddr, &clen);
        printf("client: %s\n", buffer);
        if(strcmp(buffer, "exit") == 0){
            break;
        }
        printf("server: ");
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        sendto(server,buffer,sizeof(buffer),0,(struct sockaddr*)&cliAddr,clen);


    }
    close(server);
    return 0;
}
