#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int min(int *visited, int *posx, int *posy, int **a, int V)//a is weight matrix
{
	int min=INT_MAX,i,j;
	
	for(i=0;i<V;i++)
	{
		if(visited[i]==1)
		{
			for(j=0;j<V;j++)
			{
				if(a[i][j]<min && visited[j]!=1)
				{
					min=a[i][j];
					*posx=i;
					*posy=j;
				}
			}
		}
	}

	a[*posx][*posy]=a[*posy][*posx]=INT_MAX;//so that it is never selected again as a min weight edge

	return min;//min weight associated with posx-posy edge
}

int notVisited(int *visited, int V)
{
	int i;
	
	for(i=0;i<V;i++)
		if(visited[i]==0)//there exists non visited, return true
			return 1;
			
	return 0;
}

void init_cost(int **cost, int V)
{
	int i,j;
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			cost[i][j]=INT_MAX;
	
}

void init_dist(int **a, int V, FILE *fp)
{
	int i,j;
	
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			fscanf(fp,"%d", &a[i][j]);
}

void printCostMatrix(int **cost, int V)
{
	int i,j;
	
	for(i=0;i<V;i++)
	{
		for(j=0;j<V;j++)
		{
			if(cost[i][j]==INT_MAX)
				printf("- ");
			else
				printf("%d  ", cost[i][j]);
		}
		
		printf("\n");
	}
}


void prims(int **a, int **cost, int V)
{
	int *visited, posx,posy;
	visited=(int *)malloc(V*sizeof(int));
	init_cost(cost,V);
	
	visited[0]=1;
	//while all are not visited, call min and adjust weights
	
	while(notVisited(visited,V))
	{
		int w=min(visited,&posx,&posy,a,V);
		cost[posx][posy]=cost[posy][posx]=w;
		
		if(visited[posx]!=1)
			visited[posx]=1;
			
		if(visited[posy]!=1)
			visited[posy]=1;		
	}

	printCostMatrix(cost, V);
}


int main()
{
	FILE *fp;
	int **a, **cost, V,i;
	
	
	if((fp=fopen("prims.txt","r"))==NULL)
	{
		printf("Could not find file.\n");
		return 0;
	}
	
	fscanf(fp,"%d",&V);
	
	a=(int **)malloc(V*sizeof(int *));
	for(i=0;i<V;i++)
		a[i]=(int *)malloc(V*sizeof(int));
		
	cost=(int **)malloc(V*sizeof(int *));
	for(i=0;i<V;i++)
		cost[i]=(int *)malloc(V*sizeof(int));		
	
	init_dist(a,V,fp);
	
	prims(a,cost,V);
	
	
	return 0;
}



