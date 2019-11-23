#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct
{
	int src;
	int dest;
	int weight;

}Edge;

typedef struct
{
	int V;
	int E;
	
	Edge *edge;//1D array of edges	

}Graph;

Graph *createGraph(int V, int E)
{
	Graph *graph;
	
	graph=(Graph *)malloc(sizeof(Graph));
	graph->V=V;
	graph->E=E;
	graph->edge=(Edge *)malloc(E*sizeof(Edge));
	
	return graph;
}

void init_graph(Graph *graph, FILE *fp)
{
	int i;
	
	for(i=0;i<graph->E;i++)
	{
		fscanf(fp,"%d",&(graph->edge[i].src));
		fscanf(fp,"%d",&(graph->edge[i].dest));
		fscanf(fp,"%d",&(graph->edge[i].weight));
	}
}


void init_dist(int *dist, int V)
{
	int i;
	dist[0]=0;
	for(i=1;i<V;i++)
		dist[i]=INT_MAX;
}

int bellf(Graph *graph, int V, int E, int *dist, int *parent)
{
	//for v-1 times
	//go through each edge
	//relax each edge
	
	int i,e;
	parent[0]=0;//parent of source=0 is itself
	
	init_dist(dist,V);
	
	for(i=1;i<=V-1;i++)
	{
		for(e=0;e<E;e++)
		{
			int u=graph->edge[e].src;
			int v=graph->edge[e].dest;
			int w=graph->edge[e].weight;
			
			if(dist[u]!=INT_MAX && dist[u]+w<dist[v])
			{
				dist[v]=dist[u]+w;
				parent[v]=u;
			}
		}
	}
	
	for(e=0;e<E;e++)
	{
		int u=graph->edge[e].src;
		int v=graph->edge[e].dest;
		int w=graph->edge[e].weight;
		
		if(dist[u]!=INT_MAX && dist[u]+w<dist[v])
		{
			printf("There is a negative weight cycle.\n");
			return 0;
		}
	}

	return 1;
}

void printSol(int *parent, int V, int strt)
{
	//print bellman ford solution
	int i;
	
	for(i=strt;i!=0;i=parent[i])
		printf("%d<-%d, ",i,parent[i]);
	printf("\n");
}


int main()
{
	FILE *fp;
	int V,E,res, *parent, *dist; Graph *graph;
	
	if((fp=fopen("bellf.txt","r"))==NULL)
	{
		printf("File not found.\n");
		return 0;
	}
	
	fscanf(fp,"%d",&V);
	fscanf(fp,"%d",&E);
	
	parent=(int *)malloc(V*sizeof(int));
	dist=(int *)malloc(V*sizeof(int));
	
	graph=createGraph(V,E);
	init_graph(graph,fp);
	res=bellf(graph,V,E,dist,parent);
	
	if(res==1)
		printSol(parent, V, 1);
	
	return 0;
}


