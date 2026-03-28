#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#include<sys/select.h>
#define port 1234
int main()
{
   int csock;
   struct sockaddr_in addr;
   socklen_t addrsize;
   int base=0,next=0,ack;
   csock=socket(AF_INET,SOCK_STREAM,0);
   if(csock<0)
   {
      printf("Error in creating client socket!\n");
      return 0;
   }
   printf("Client socket created successfully!\n");
   memset(&addr,0,sizeof(addr));
   addr.sin_family=AF_INET;
   addr.sin_port=htons(port);
   addr.sin_addr.s_addr=inet_addr("127.0.0.1");
   connect(csock,(struct sockaddr*)&addr,sizeof(addr));
   while(base<5)
   {
      while(next<4+base&&next<5)
      {
         printf("Sending frame %d\n",next);
         send(csock,&next,sizeof(next),0);
         next++;
      }
      fd_set readfds;
      struct timeval tv;
      FD_ZERO(&readfds);
      FD_SET(csock,&readfds);
      tv.tv_sec=3;
      tv.tv_usec=0;
      int activity=select(csock+1,&readfds,NULL,NULL,&tv);
      if(activity>0)
      {
         recv(csock,&ack,sizeof(ack),0);
         printf("Received ACK %d\n",ack);
         base=ack+1;
      }
      else
      {
         printf("Timeout.Resending frame %d\n",base);
         next=base;
      }
      sleep(1);
   }
   int end=-1;
   send(csock,&end,sizeof(end),0);
   close(csock);
   return 0;
}
