#include<stdio.h>
#include<stdlib.h>
#define inf 999
int main()
{
   int n,i,j,k;
   int cost[100][100],dist[100][100],next[100][100];
   printf("Enter the number of routers:");
   scanf("%d",&n);
   printf("Enter the cost matrix(999 for infinity)\n");
   for(i=0;i<n;i++)
   {
      for(j=0;j<n;j++)
      {
         scanf("%d",&cost[i][j]);
         dist[i][j]=cost[i][j];
         if(i==j)
         {
            next[i][j]=i;
         }
         else if(cost[i][j]!=inf)
         {
            next[i][j]=j;
         }
         else
         {
            next[i][j]=-1;
         }
      }
   }
   for(k=0;k<n;k++)
   {
      for(i=0;i<n;i++)
      {
         for(j=0;j<n;j++)
         {
            if(dist[i][j]>dist[i][k]+dist[k][j])
            {
               dist[i][j]=dist[i][k]+dist[k][j];
               next[i][j]=next[i][k];
            }
         }
      }
   }
   for(i=0;i<n;i++)
   {
      printf("\nRouter%d\n",i);
      printf("Destination Distance Next Router\n");
      for(j=0;j<n;j++)
      {
         printf("%d\t",j);
         if(dist[i][j]>=inf)
         {
            printf("-1\t");
         }
         else
         {
            printf("%d\t",dist[i][j]);
         }
         printf("%d\n",next[i][j]);
      }
   }
   printf("Cost Matrix\n  \t");
   for(i=0;i<n;i++)
   {
      printf("%d\t",i);
   }
   printf("\n");
   for(i=0;i<n;i++)
   {
      printf("%d |\t",i);
      for(j=0;j<n;j++)
      {
         printf("%d\t",dist[i][j]);
      }
      printf("\n");
   }
   return 0;
}
