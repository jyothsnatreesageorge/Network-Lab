#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/select.h>
#define port 1234
int main()
{
    int ssock,csock,i,n;
    struct sockaddr_in addr;
    socklen_t addrsize;
    int client[10],clientid[10],cno=1,count=0,max_sd;
    char b[1024];
    ssock=socket(AF_INET,SOCK_STREAM,0);
    if(ssock<0)
    {
        printf("Error in creating server socket!\n");
        return 0;
    }
    printf("Server socket created successfully!");
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(ssock,(struct sockaddr*)&addr,sizeof(addr));
    listen(ssock,5);
    printf("Server listening!\n");
    for(i=0;i<10;i++)
    {
        client[i]=0;
    }
    while(1)
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(ssock,&readfds);
        max_sd=ssock;
        for(i=0;i<10;i++)
        {
            if(client[i]>0)
            {
                FD_SET(client[i],&readfds);
            }
            if(client[i]>max_sd)
            {
                max_sd=client[i]
            }
        }
        select(max_sd+1,&readfds,NULL,NULL,NULL);
        if(FD_ISSET(ssock,&readfds))
        {
            addrsize=sizeof(addr);
            csock=accept(ssock,(struct sockaddr*)&addr,&addrsize);
            for(i=0;i<10;i++)
            {
                if(client[i]==0)
                {
                    client[i]=csock;
                    clientid[i]=cno++
                    count++;
                    printf("Client %d connected!\n",clientid[i]);
                    break;
                }
            }
        }
        for(i=0;i<10;i++)
        {
            if(FD_ISSET(client[i],&readfds))
            {
                n=recv(csock,b,sizeof(b),0);
                if(n<=0)
                {
                    printf("Client %d disconnected\n",clientid[i]);
                    count--;
                    client[i]=0;
                    close(client[i]);
                    if(count==0)
                    {
                        printf("Server disconnected!\n");
                        close(ssock);
                        return 0;
                    }
                    continue;
                }
                b[n]='\0';
                if(strncmp(b,"exit",4)==0)
                {
                    printf("Client %d disconnected\n",clientid[i]);
                    count--;
                    client[i]=0;
                    close(client[i]);
                    if(count==0)
                    {
                        printf("Server disconnected!\n");
                        close(ssock);
                        return 0;
                    }
                    continue;
                }
                else
                {
                    char msg[1000];
                    snprintf(msg,"Client %d:%s",clientid[i],b);
                    printf("%s",msg);
                    for(int j=0;j<10;j++)
                    {
                        if(client[j]!=0&&j!=i)
                        {
                            send(msg,sizeof(msg),0);
                        }
                    }
                }
            }
        }
    }
    return 0;
}