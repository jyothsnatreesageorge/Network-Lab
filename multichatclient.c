#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/select.h>
#define port 1234
int main()
{
    int csock,i,n;
    struct sockaddr_in addr;
    socklen_t addrsize;
    int client[10],clientid[10],cno=1,count=0,max_sd;
    char b[1024];
    csock=socket(AF_INET,SOCK_STREAM,0);
    if(csock<0)
    {
        printf("Error in creating server socket!\n");
        return 0;
    }
    printf("Server socket created successfully!");
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(csock,(struct sockaddr*)&addr,sizeof(addr))
    if(fork()==0)
    {
        while(1)
        {
            bzero(b,1024);
            recv(csock,b,sizeof(b),0);
            printf("%s",b);
        }
    }
    while(1)
    {
        bzero(b,1024);
        fgets(b,sizeof(b),stdin);
        send(csock,b,sizeof(b),0);
        if(strncmp(b,"exit",4)==0)
        {
            printf("Client disconnecting\n");
            close(csock);
        }
    }
    return 0;
}