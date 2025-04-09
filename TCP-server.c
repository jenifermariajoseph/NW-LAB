#include<stdio.h>
#include<string.h>
#include<stdlib.h>>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
    int server, client, port;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024]={0};
    socklen_t clen=sizeof(cliaddr);
    #define PORT 8080

    // Create socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
 
    
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to the port
    bind(server, (struct sockaddr*)&servaddr, sizeof(servaddr)); ;

    // Listen for incoming connections
    listen(server, 5);
    printf("\nWaiting for client connection...\n");

    client = accept(server, (struct sockaddr*)&cliaddr, &clen);

    printf("\nClient connected.\n");

    while(1){
        memset(buffer,0,sizeof(buffer));
        read(client,buffer,sizeof(buffer));
        printf("client:%s\n",buffer);
        if(strcmp(buffer,"exit")==0){
            break;
        }   
        printf("server:");
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        send(client,buffer,sizeof(buffer),0);
    }

    // Close sockets
    close(client);
    close(server);

    return 0;
}
