#include<stdio.h>
#include<stdlib.h>


void printSol(int colour[], int V)
{
	int i;
	
	for(i=0;i<V;i++)
		printf("Colour %d for vertex %d.\n", colour[i],i+1);
}


int isSafe(int v, int **graph, int colour[], int c, int V)
{
	//v is vertex which will be marked with colour c, V*V graph, colour array
	
	int i;
	
	for(i=0;i<V;i++)//adjacent vertices same colour return false
		if(graph[v][i]!=0 && colour[i]==c)
			return 0;//false
	return 1;//true
}

//main algo with backtracking
int graphcol(int **graph,int m, int colour[],int v, int V)
{
	int c;
	if(v==V)
		return 1;//solution exists, base case
		
	for(c=1;c<=m;c++)
	{
		if(isSafe(v,graph,colour,c,V))
		{
			colour[v]=c;
			
			if(graphcol(graph,m,colour,v+1,V)==1)//recursive backtracking step
				return 1;
				
			colour[v]=0;	
		}
	}
		
	return 0;
}


void gcolpossible(int **graph, int m, int V)
{
	int i;
	int *colour=(int *)malloc(V*sizeof(int));
	
	for(i=0;i<V;i++)
		colour[i]=0;
		
	if(graphcol(graph,m,colour,0,V)==0)
		printf("Not possible\n");
	else
	{
		printf("Solution is possible.\n");
		printSol(colour,V);
	} 
}


int main()
{
	FILE *fp; int **graph,m,V,i,j;
	
	if((fp=fopen("gcol.txt", "r"))==NULL)
	{
		printf("File not found!\n");
		return 0;
	}

	fscanf(fp,"%d", &m);//take input for number of colours
	fscanf(fp,"%d", &V);//no of vertices
	
	graph=(int **)malloc(V*sizeof(int *));//allocate graph
	for(i=0;i<V;i++)
		graph[i]=(int *)malloc(V*sizeof(int));
		
	
	for(i=0;i<V;i++)//take input for graph
		for(j=0;j<V;j++)
			fscanf(fp,"%d", &graph[i][j]);
			
	
	gcolpossible(graph,m,V);

	return 0;
}
