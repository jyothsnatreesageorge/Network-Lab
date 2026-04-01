#include<stdio.h>
#include<stdlib.h>
int main()
{
   int size,rate,packet[100],dropped[100],n,i,j,current=0;
   printf("Enter bucket size:");
   scanf("%d",&size);
   printf("Enter output rate:");
   scanf("%d",&rate);
   printf("Enter the number of packets:");
   scanf("%d",&n);
   printf("Enter packet sizes\n");
   for(i=0;i<n;i++)
   {
      scanf("%d",&packet[i]);
   }
   printf("Time\tPacket\tBucket\tOutput\tDrop\tRem\n");
   printf("0\t-\t0\t-\t-\t-\n");
   for(i=0;i<n;i++)
   {
      int drop=0;
      if(current+packet[i]<=size)
      {
         current+=packet[i];
      }
      else
      {
         drop=(current+packet[i])-size;
         current=size;
      }
      if(current<rate)
      {
         printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,packet[i],current,current,drop,0);
         current=0;
      }
      else
      {
         printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,packet[i],current,rate,drop,current-rate);
         current-=rate;
      }
   }
   return 0;
}
