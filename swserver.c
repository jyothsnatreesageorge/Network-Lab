#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/arpa.h>
#include<time.h>
#define port 1234
int main()
{
    int ssock,csock;
    struct sockaddr_in addr;
    socklen_t addrsize;
    int ack,frame,expected=0;
    srand(time(NULL));
    ssock=socket(AF_INET,SOCK_STREAM,0);
    if(ssock<0)
    {
        printf("Error in creating server socket!\n");
        return 0;
    }
    printf("Server socket created successfully!\n");
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(sscok,(struct sockaddr *)&addr,sizeof(addr));
    listen(ssock,5);
    printf("Server listening!\n");
    addrsize=sizeof(addr);
    csock=accept(ssock,(struct sockaddr*)&addr,&addrsize);
    if(csock<0)
    {
        printf("Error in creating client socket!\n");
        return 0;
    }
    printf("Client connected!\n");
    while(1)
    {
        recv(csock,&frame,sizeof(frame),0);
        if(frame==-1)
        {
            break;
        }
        printf("Frame %d received\n",frame);
        int loss=rand()%3;
        if(loss==0)
        {
            printf("ACK Lost\n");
        }
        else
        {
            ack=frame-1;
            printf("Sending ack %d\n",ack);
            send(csock,&ack,sizeof(ack),0);
        }
    }
    close(csock);
    close(ssock);
    return 0;
}