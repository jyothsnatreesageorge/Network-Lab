#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define port 1234
int main()
{
   int csock;
   struct sockaddr_in addr;
   socklen_t addrsize;
   char b[1024];
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
   connect(csock,(struct sockaddr *)&addr,sizeof(addr));
   printf("Enter filename:");
   scanf("%s",b);
   send(csock,b,strlen(b),0);
   bzero(b,1024);
   recv(csock,b,sizeof(b),0);
   printf("Serevr response:%s\n",b);
   close(csock);
   return 0;
}
