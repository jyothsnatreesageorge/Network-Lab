#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define port 1234
int main()
{
   int csock;
   struct sockaddr_in addr;
   socklen_t addrsize;
   char b[1024];
   csock=socket(AF_INET,SOCK_DGRAM,0);
   if(csock<0)
   {
      printf("Client socket not created!\n");
      return 0;
   }
   printf("Client socket created successfully!\n");
   addr.sin_family=AF_INET;
   addr.sin_port=htons(port);
   addr.sin_addr.s_addr=inet_addr("127.0.0.1");
   addrsize=sizeof(addr);
   while(1)
   {
      bzero(b,1024);
      printf("Enter the message:");
      fgets(b,sizeof(b),stdin);
      sendto(csock,b,sizeof(b),0,(struct sockaddr *)&addr,addrsize);
      if(strncmp(b,"exit",4)==0)
      {
         close(csock);
         break;
      }
      bzero(b,1024);
      recvfrom(csock,b,sizeof(b),0,(struct sockaddr*)&addr,&addrsize);
      printf("Server:%s",b);
      if(strncmp(b,"exit",4)==0)
      {
         close(csock);
         break;
      }
   }
   return 0;
}
