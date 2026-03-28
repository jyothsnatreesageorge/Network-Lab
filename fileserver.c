#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define port 1234
int main()
{
   int ssock,csock;
   struct sockaddr_in addr;
   socklen_t addrsize;
   char b[1024],file[256],content[1024];
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
   printf("Server listening!\n");
   while(1)
   {
      addrsize=sizeof(addr);
      csock=accept(ssock,(struct sockaddr *)&addr,&addrsize);
      printf("Client connected!");
      if(fork()==0)
      {
         close(ssock);
         int n=recv(csock,file,255,0);
         file[n]='\0';
         printf("Client %d req file %s\n",getpid(),file);
         FILE* fd=fopen(file,"r");
         if(fd)
         {
            n=fread(content,1,1023,fd);
            content[n]='\0';
            fclose(fd);
            snprintf(b,sizeof(b),"Client %d\nFile content:%s\n",getpid(),content);
         }
         else
         {
            snprintf(b,sizeof(b),"Client %d\nError file doesnot exist\n",getpid());
         }
         send(csock,b,strlen(b),0);
         printf("Response sent to Client %d\nCLosing connection\n",getpid());
         close(csock);
         exit(0);
      }
      close(csock);
   }
   return 0;
}
