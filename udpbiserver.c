#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define port 1234
int main()
{
   int ssock;
   struct sockaddr_in addr;
   socklen_t addrsize;
   char b[1024];
   ssock=socket(AF_INET,SOCK_DGRAM,0);
   if(ssock<0)
   {
      printf("Server socket could not be created!\n");
      return 0;
   }
   printf("Server socket created successfully!\n");
   memset(&addr,0,sizeof(addr));
   addr.sin_family=AF_INET;
   addr.sin_port=htons(port);
   addr.sin_addr.s_addr=inet_addr("127.0.0.1");
   addrsize=sizeof(addr);
   bind(ssock,(struct sockaddr *)&addr,sizeof(addr));
   while(1)
   {
      bzero(b,1024);
      recvfrom(ssock,b,sizeof(b),0,(struct sockaddr*)&addr,&addrsize);
      printf("Client:%s",b);
      if(strncmp(b,"exit",4)==0)
      {
         close(ssock);
         break;
      }
      bzero(b,1024);
      printf("Enter the message:");
      fgets(b,sizeof(b),stdin);
      sendto(ssock,b,sizeof(b),0,(struct sockaddr *)&addr,addrsize);
      if(strncmp(b,"exit",4)==0)
      {
         close(ssock);
         break;
      }
   }
   return 0;
}
