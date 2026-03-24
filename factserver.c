#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define port 1234
int main()
{
   int ssock,csock;
   struct sockaddr_in addr;
   socklen_t addrsize;
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
   bind(ssock,(struct sockaddr *)&addr,sizeof(addr));
   listen(ssock,5);
   printf("Server listening\n");
   addrsize=sizeof(addr);
   csock=accept(ssock,(struct sockaddr *)&addr,&addrsize);
   char num[100];
   int n,i,fact=1;
   bzero(num,100);
   recv(csock,num,sizeof(num),0);
   n=atoi(num);
   printf("Number sent from client:%d\n",n);
   for(i=1;i<=n;i++)
   {
      fact=fact*i;
   }
   printf("The factorial of the number %d is %d\n",n,fact);
   bzero(num,100);
   snprintf(num,sizeof(num),"The factorial of %d is %d",n,fact);
   send(csock,num,sizeof(num),0);
   close(csock);
   close(ssock);
   return 0;
}

