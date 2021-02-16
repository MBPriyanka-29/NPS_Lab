#include<stdio.h>
#define N 100
int A[N][N],d[N],p[N],n;

void bellamford(int s)
{
	int u,v,i;
	
	for(i=0;i<n;i++)
	{
		for(u=0;u<n;u++)
		{
			for(v=0;v<n;v++)
			{
				if(d[v]>d[u]+A[u][v])
				{
					d[v]=d[u]+A[u][v];
					p[v]=u;
				}
			}
		}
	}
	for(u=0;u<n;u++)
			for(v=0;v<n;v++)
				if(d[v]>d[u]+A[u][v])
					printf("\n Negative edge!");
		
}
int main()
{
	int i,j,s,dest;
	printf("Enter the no. of vertices : ");
	scanf("%d",&n);
	printf("Enter the adjacency matrix\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&A[i][j]);
	printf("\n");
	int source;
	for(source=0;source<n;source++){
	printf("Source : %d\n",source);
		for(i=0;i<n;i++){
			d[i] = 999;
			p[i] = -1;
		}

	// YOU FORGOT THIS ONCE
	d[source]=0; // source->source 0

	bellamford(source);
	for(i=0;i<n;i++)
	{
		if(i!=source)
		{
		j=i;
		while(p[j]!=-1)
			{
				printf("%d<-",j);
				j=p[j];
			}
		}
		printf("%d\t\t Cost : %d\n",source,d[i]);
		
	}
printf("\n");
	}
 	printf("\n Enter source and destination node : ");
	scanf("%d %d",&s,&dest);
	source=s;

	printf("Source : %d\n",source);
		for(i=0;i<n;i++){
			d[i] = 999;
			p[i] = -1;
		}
	
	d[source]=0; // source->source 0

	bellamford(source);
	j=dest;
	while(p[j]!=-1)
		{
			printf("%d<-",j);
			j=p[j];
		}
	printf("%d\t\t Cost : %d\n",source,d[dest]);
	
	return 0;
	
}
/*
0 1 5
1 0 2
5 2 0
*/

