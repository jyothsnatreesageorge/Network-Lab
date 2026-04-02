#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#define port 1234
int main()
{
   int ssock,n;
   struct sockaddr_in serv,cli;
   socklen_t addrsize;
   char b[1024],str[1024];
   ssock=socket(AF_INET,SOCK_DGRAM,0);
   if(ssock<0)
   {
      printf("Error in creating server socket!\n");
      return 0;
   }
   printf("Server socket created successfully!\n");
   memset(&serv,0,sizeof(serv));
   serv.sin_family=AF_INET;
   serv.sin_port=htons(port);
   serv.sin_addr.s_addr=INADDR_ANY;
   bind(ssock,(struct sockaddr *)&serv,sizeof(serv));
   printf("Server connected!\n");
   while(1)
   {
      addrsize=sizeof(cli);
      n=recvfrom(ssock,b,sizeof(b),0,(struct sockaddr *)&cli,&addrsize);
      b[n]='\0';
      if(strncmp(b,"TIME",4)==0)
      {
         time_t now=time(NULL);
         char* time_str=ctime(&now);
         printf("Time request from client%s:%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
         printf("Time sent:%s\n",time_str);
         sendto(ssock,time_str,strlen(time_str),0,(struct sockaddr *)&cli,addrsize);
      }
   }
   close(ssock);
   return 0;
}
