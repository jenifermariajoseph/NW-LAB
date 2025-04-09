#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>

#define PORT 8080

int main(){
    int server, client;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clen = sizeof(cliaddr);
    int packet;

    srand(time(NULL)); // Seed for random number generation
    server = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    bind(server, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(server, 1);
    client = accept(server, (struct sockaddr*)&cliaddr, &clen);
    while(recv(client, &packet, sizeof(packet),0)>0){
        printf("Received packet: %d\n", packet);
        if(rand()%3 ==0){
            printf("ACK lost for packet: %d\n\n", packet);
            sleep(1);
            continue;
        }
        send(client, "ACK", strlen("ACK"), 0);
        printf("ACK sent for packet: %d\n\n", packet);
    }
    close(client);
    close(server);
    return 0;
}
