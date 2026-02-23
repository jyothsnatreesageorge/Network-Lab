#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define port 1234
int main()
{
    int ssock,csock;
    struct sockaddr_in addr;
    socklen_t addrsize;
    char b[1024];
    ssock=socket(AF_INET,SOCK_STREAM,0);
    if(ssock<0)
    {
        printf("Server socket is not created!\n");
        return 0;
    }
    printf("Server socket created successfully!\n");
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(ssock,(struct sockaddr*)&addr,sizeof(addr));
    printf("Server binded to port successfully!\n");
    listen(ssock,5);
    printf("Server listening\n");
    addrsize=sizeof(addr);
    csock=accept(ssock,(struct sockaddr*)&addr,&addrsize);
    printf("Client connected!\n");
    while(1)
    {
        bzero(b,1024);
        recv(csock,b,sizeof(b),0);
        printf("Client:%s\n",b);
        if(strncmp(b,"exit",4)==0)
        {
            close(csock);
            close(ssock);
            printf("Client disconnected!\n");
            break;
        }
    }
    return 0;
}