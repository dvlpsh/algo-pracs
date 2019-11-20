#include<stdio.h>
#include<stdlib.h>

//this struct represents an edge
typedef struct
{
	int src; //source vertex of the edge
	int dest; //dest vertex of the edge
}Edge;

//this struct represents a graph
typedef struct
{
	int V; // no of vertices
	int E; //no of edges

	Edge* edge; //1D array of edges
}Graph;

//struct for subset->subset a vertex belongs to and its parent
typedef struct 
{
	int parent; //parent of the current vertex
	int rank; //rank of the vertex
}subset;



//function to create a Graph, with vertex set V and E Edges
Graph* createGraph(int V, int E, FILE* fp)
{
	//graph having V vertices, E edges, edge array
	Graph* graph = (Graph *)malloc(sizeof(Graph));
	graph->V=V;
	graph->E=E;
	
	//create Edge array
	graph->edge=(Edge *)malloc(graph->E*sizeof(Edge));
	
	//taking input
	for(int i=0;i<E;i++)
	{
		fscanf(fp,"%d", &graph->edge[i].src);
		fscanf(fp,"%d", &graph->edge[i].dest);
	}	
	
	return graph;//return the graph
}


//find the subset of a vertex, return subset of a vertex
//takes subsets array and finds which subset vertex v belongs
int find(subset subsets[], int v)
{
	//find root of v and make it its parent, collapsing find
	if(subsets[v].parent>0)//if v is not a parent of itself
		subsets[v].parent=find(subsets, subsets[v].parent);
	
	return subsets[v].parent;
}


//perform union of 2 sets based on rank
void Union(subset subsets[], int x, int y)
{

	int xroot=find(subsets,x);
	int yroot=find(subsets,y);
	
	if(subsets[xroot].rank>subsets[yroot].rank)
		subsets[xroot].parent=yroot;
	
	else if(subsets[xroot].rank<subsets[yroot].rank)
		subsets[yroot].parent=xroot;
		
	else //if ranks are equal
	{
		subsets[yroot].parent=xroot;
		subsets[xroot].rank--;
	}
}


//check for cycle in graph
int checkCycle(Graph* graph)
{
	int V=graph->V;
	int E=graph->E;
	
	subset* subsets=(subset *)malloc(V*sizeof(subset));
	
	for(int v=0;v<V;v++)
	{
		subsets[v].parent=-1;
		subsets[v].rank=0;
	}

	for(int e=0;e<E;e++)
	{
		int x=find(subsets,graph->edge[e].src);
		int y=find(subsets,graph->edge[e].dest);
		
		if(x==y)
			return 1;
		
		Union(subsets,x,y);
	}
	
	return 0;
}


int main()
{
	FILE* fp; int v,e; Graph *graph;
	
	if((fp=fopen("unfi.txt","r"))==NULL)
	{
		printf("File not found!");
		return 0;
	}
	
	
	fscanf(fp,"%d", &v);
	fscanf(fp,"%d", &e);
	
	graph = createGraph(v,e,fp);
	
	if(checkCycle(graph))
		printf("Cycle is present\n");
	else
		printf("Cycle is NOT present\n");	
	
	return 0;
}
