#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
void reverse(char *str, int len) {
    int i = 0, j = len - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
int main(){
int server,client;
struct sockaddr_in servaddr,cliaddr;
char buffer[1024]={0};
socklen_t clen=sizeof(cliaddr);
server = socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(PORT);
bind(server,(struct sockaddr*)&servaddr,sizeof(servaddr));
listen(server,5);
client=accept(server,(struct sockaddr*)&cliaddr,&clen);

while(1){
    memset(buffer,0,sizeof(buffer));
    read(client,buffer,sizeof(buffer));
    printf("client: %s\n",buffer);
    FILE *fp=fopen(buffer,"r");
 
    if(fp == NULL){
        strcpy(buffer, "File not found");
        send(client, buffer, sizeof(buffer), 0);
        continue;
    }
    while(!feof(fp)){
       int bytes=fread(buffer,1,sizeof(buffer),fp);
       reverse(buffer, bytes); 
       send(client,buffer,bytes,0);

    }
    if(strcmp(buffer,"exit")==0){
        break;
    }
    fclose(fp);

}

close(server);
return 0;


}