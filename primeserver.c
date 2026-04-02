#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define port 1234
int main()
{
   int ssock;
   struct sockaddr_in addr,caddr;
   socklen_t addrsize;
   char num[100];
   ssock=socket(AF_INET,SOCK_DGRAM,0);
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
   addrsize=sizeof(caddr);
   bind(ssock,(struct sockaddr *)&addr,sizeof(addr));
   recvfrom(ssock,num,sizeof(num),0,(struct sockaddr *)&caddr,&addrsize);
   int n=atoi(num);
   printf("Number from Client:%d\n",n);
   int i,flag;
   char s[1024];
   for(i=2;i<=(n/2);i++)
   {
      flag=0;
      if(n%i==0)
      {
         flag=1;
         break;
      }
   }
   if(flag==0)
   {
      printf("The received number is prime number\n");
      bzero(s,1024);
      snprintf(s,sizeof(s),"%d is a prime number\n",n);
      sendto(ssock,s,sizeof(s),0,(struct sockaddr *)&caddr,addrsize);
      bzero(s,1024);
      snprintf(s,sizeof(s),"The factors of %d are 1 and %d\n",n,n);
      sendto(ssock,s,sizeof(s),0,(struct sockaddr *)&caddr,addrsize);
   }
   else
   {
      printf("The received number is not prime number\n");
      bzero(s,1024);
      snprintf(s,sizeof(s),"%d is a composite number\n",n);
      sendto(ssock,s,sizeof(s),0,(struct sockaddr *)&caddr,addrsize);
      bzero(s,1024);
      snprintf(s,sizeof(s),"Composite number has other factors other than 1 and number itself\n");
      sendto(ssock,s,sizeof(s),0,(struct sockaddr *)&caddr,addrsize);
   }
   close(ssock);
   return 0;
}
