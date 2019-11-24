#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void init_dist(int **dist, int V, FILE *fp)
{
	int i,j;
	
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			fscanf(fp,"%d", &dist[i][j]);
}

void printSol(int **dist, int V)
{
	int i,j;
	
	for(i=0;i<V;i++)
	{
		for(j=0;j<V;j++)
		{
			if(dist[i][j]==1000)
				printf("INF ");
			else
				printf("%d ", dist[i][j]);
		}
		
		printf("\n");
	}
	
	printf("\n");
}


void floyd(int **dist, int V)
{
	int i,j,k;
	
	for(k=0;k<V;k++)
	{
		for(i=0;i<V;i++)
		{
			for(j=0;j<V;j++)
			{
				if(dist[i][k]+dist[k][j]<dist[i][j])
					dist[i][j]=dist[i][k]+dist[k][j];
			}
		}
	}
	
	printSol(dist,V);
}



int main()
{
	FILE *fp;
	int V, **dist, i;
	
	if((fp=fopen("floydwar.txt","r"))==NULL)
	{
		printf("Could not find file.\n");
		return 0;
	}
	
	
	fscanf(fp,"%d",&V);
	
	dist=(int **)malloc(V*sizeof(int *));
	for(i=0;i<V;i++)
		dist[i]=(int *)malloc(V*sizeof(int));		
	
	init_dist(dist,V,fp);
	floyd(dist,V);


	return 0;
}







