#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080

int main(){
int server;
struct sockaddr_in servaddr,cliaddr;
char buffer[1024]={0};
socklen_t clen=sizeof(cliaddr);
server = socket(AF_INET,SOCK_DGRAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(PORT);
bind(server,(struct sockaddr*)&servaddr,sizeof(servaddr));

while(1){
    memset(buffer,0,sizeof(buffer));
    recvfrom(server,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&clen);
    printf("client: %s\n",buffer);
    if(strcmp(buffer,"exit")==0){
        break;
    }
    printf("server:");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\n")]='\0';
    sendto(server,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,clen);

}

close(server);
return 0;


}