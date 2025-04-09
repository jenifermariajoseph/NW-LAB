#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>

#define PORT 8080
int main(){
    int client;
    struct sockaddr_in servaddr;
    char ack[10];
    int packet=1;
    int max_packets;
    printf("Enter number of packets to send: ");
    scanf("%d", &max_packets);
    client = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    connect(client, (struct sockaddr*)&servaddr, sizeof(servaddr));
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    while(packet<=max_packets){
        printf("Sending packet: %d\n", packet);
        send(client, &packet, sizeof(packet), 0);
        int bytes=recv(client,ack, sizeof(ack), 0);
        if(bytes<0){
            printf("timeout\n");
            sleep(1);
            continue;
        }
        ack[bytes]='\0';
        if(strcmp(ack, "ACK")==0){
            printf("ACK received for packet: %d\n", packet);
            packet++;
        }
    }
    close(client);
    return 0;
}