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
   printf("Connected to server!\n");
   int n;
   char num[100];
   printf("Enter the number:");
   scanf("%d",&n);
   snprintf(num,sizeof(num),"%d",n);
   send(csock,num,sizeof(num),0);
   bzero(num,100);
   recv(csock,num,sizeof(num),0);
   printf("Server:%s\n",num);
   close(csock);
   return 0;
}

