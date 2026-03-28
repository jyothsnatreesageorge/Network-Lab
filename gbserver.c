#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#define port 1234
int main()
{
   int ssock,csock;
   struct sockaddr_in addr;
   socklen_t addrsize;
   int frame,ack,expected=0;
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
   bind(ssock,(struct sockaddr*)&addr,sizeof(addr));
   listen(ssock,5);
   printf("Server listening\n");
   addrsize=sizeof(addr);
   csock=accept(ssock,(struct sockaddr*)&addr,&addrsize);
   if(csock<0)
   {
      printf("Error in creating client socket!\n");
      return 0;
   }
   printf("Client socket created successfully!\n");
   while(1)
   {
      recv(csock,&frame,sizeof(frame),0);
      if(frame==-1)
      {
         break;
      }
      printf("Received frame %d\n",frame);
      if(frame==expected)
      {
         int loss=rand()%3;
         if(loss==0)
         {
            printf("ACK lost for frame %d\n",frame);
         }
         else
         {
            ack=frame;
            printf("Sending ACK %d\n",ack);
            send(csock,&ack,sizeof(ack),0);
            expected++;
         }
      }
      else
      {
         ack=expected-1;
         printf("Out of order.Sending last ack %d\n",ack);
         send(csock,&ack,sizeof(ack),0);
      }
      sleep(1);
   }
   close(csock);
   close(ssock);
   return 0;
}

