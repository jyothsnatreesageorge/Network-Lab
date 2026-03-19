#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/select.h>
#define port 1234
int main()
{
    int csock;
    struct soackaddr_in addr;
    socklen_t addrsize;
    csock=socket(AF_INET,SOCK_STREAM,0);
    if(csock<0)
    {
        printf("Error in creating client socket!\n");
        return 0;
    }
    printf("Client socket created successfully!\n");
    memset(&addr,0,sizoef(addr));
    addr.sin_family=AF_INET;
    adr.sin_port=htons(port);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(csock,(struct sockaddr*)&addr,sizeof(addr));
    int total=10,i=0,frame=0,activity;
    while(i<total)
    {
        printf("Sending frame %d\n",frame);
        send(csock,&frame,sizeof(frame),0);
        fd_set readfds;
        struct timeval tv;
        FD_ZERO(&readfds);
        FD_SET(csock,&readfds);
        tv.tv_sec=3;
        tv.tv_usec=0;
        activity=select(csock+1,&readfds,NULL,NULL,&tv);
        if(activity>0)
        {
            n=recv(csock,&ack,sizeof(ack),0);
            if(ack==1-frame)
            {
                printf("ACK %d received\n");
                frame=ack;
                i++;
            }
            else
            {
                printf("Wrong acknowledgement!\n");
            }
        }
        else
        {
            printf("Timeout!Resending frame %d\n",frame);
        }
        sleep(1);
    }
    int end=-1
    send(csock,&end,sizoef(end),0);
    close(csock);
    return 0;
}