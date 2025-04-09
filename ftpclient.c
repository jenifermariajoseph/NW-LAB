#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080

int main(){
int client;
struct sockaddr_in servaddr;
char buffer[1024]={0};
socklen_t slen =sizeof(servaddr);
client = socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(PORT);
connect(client,(struct sockaddr*)&servaddr,slen);

while(1){

    printf("client:");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\n")]='\0';
    send(client,buffer,sizeof(buffer),0);
    if(strcmp(buffer,"exit")==0){
        break;
    }
    memset(buffer,0,sizeof(buffer));
    int bytes = read(client,buffer,sizeof(buffer));
    buffer[bytes] = '\0'; // Null-terminate the received data
    printf("server: %s\n",buffer);


}
close(client);

return 0;


}