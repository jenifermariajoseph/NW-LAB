#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netdb.h>
#include<unistd.h>

int main(){
    int serversocket, clientsocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    char message[1000];
    socklen_t len;

    // Create socket
    serversocket = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize server address structure
    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    
    // Get port number from user
    printf("Enter the port number: ");
    scanf("%d", &port);
    
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to the port
    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) ;

    // Listen for incoming connections
    listen(serversocket, 5);
    printf("\nWaiting for client connection...\n");

    len = sizeof(clientaddr);
    clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);

    printf("\nClient connected.\n");

    // Read message from client
    bzero(message, sizeof(message));
    read(clientsocket, message, sizeof(message));
    printf("\nMessage from the client: %s\n", message);

    // Send response to client
    printf("\nSending response to the client...\n");
    write(clientsocket, "YOUR MESSAGE RECEIVED.", strlen("YOUR MESSAGE RECEIVED."));

    // Close sockets
    close(clientsocket);
    close(serversocket);

    return 0;
}
