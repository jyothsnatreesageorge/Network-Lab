#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<time.h>
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
      printf("Error in creating client socket!\n");
      return 0;
   }
   printf("Client socket created successfully!\n");
   memset(&addr,0,sizeof(addr));
   addr.sin_family=AF_INET;
   addr.sin_port=htons(port);
   addr.sin_addr.s_addr=inet_addr("127.0.0.1");
   addrsize=sizeof(addr);
   printf("Enter TIME to request for time:");
   fgets(b,sizeof(b),stdin);
   b[strcspn(b,"\n")] = '\0';
   sendto(csock,b,strlen(b),0,(struct sockaddr *)&addr,addrsize);
   int n=recvfrom(csock,b,sizeof(b),0,NULL,NULL);
   b[n]='\0';
   printf("Time sent from server:%s\n",b);
   close(csock);
   return 0;
}
