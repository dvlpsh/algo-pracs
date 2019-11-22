#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MIN(a,b) ((a<b)?a:b)

typedef struct ll
{
	int data;
	struct ll *next;

}node;


typedef struct
{
	node *head;
		
}queue;


node* getNode()
{
	return ((node *)malloc(sizeof(node)));
}

void init(queue *q)
{
	q->head=NULL;
}

void enqueue(node **head, int d)
{
	node *temp;
	temp = getNode();
	temp->data = d;
	temp->next = NULL;
	
	if(*head == NULL)//if no node exists, make temp as head
		*head = temp;
		
	else
	{
		node *temp2;
		temp2 = *head;
		while(temp2->next!= NULL)
			temp2 =temp2->next;
			
		temp2->next = temp;
	}

}

int dequeue(node **head)
{
	node *temp=NULL;
	int v;
	temp=*head;
	v=temp->data; //return the data of head
	*head=(*head)->next;
	free(temp);
	
	return v;	
}

int isEmpty(node *head)
{
	return (head==NULL);
}

int front(node* head)
{
	return (head->data);
}


int bfs(int V, int **residual, int s, int t, int parent[])
{
	int i; queue q;
	
	int *visited=(int *)malloc(V*sizeof(int));
	
	for(i=0;i<V;i++)
		visited[i]=0;//initally all are unvisited
		
	enqueue(&(q.head),s);//enqueue source
	visited[s]=1;//mark it as visited
	parent[s]=-1;//there is no parent of source
	
	//BFS
	while(!isEmpty(q.head))
	{
		int u=dequeue(&(q.head));
		
		for(v=0;v<V;v++)
		{
			if(visited[v]==0 && residual[u][v]>0)//path exists
			{
				enqueue(&(q.head),v);//enqueue the vertex
				parent[v]=u;//ste parent of v as current vertex
				visited[v]=1;//marked v as visited
			}
		}
		
	}
	
	return (visited[t]==1);//dest is visited then path exists
}


int fordful(int **graph, int s, int t, int V)
{
	int u,v,i;
	
	int **residual=(int **)malloc(V*sizeof(int *));
	for(i=0;i<V;i++)
		residual[i]=(int *)malloc(V*sizeof(int));
		
	for(u=0;u<V;u++)
		for(v=0;v<V;v++)
			residual[u][v]=graph[u][v];
	
	int *parent=(int *)malloc(V*sizeof(int));
	int max_flow=0;
	
	
	while(bfs(V,residual,s,t,parent))//while path exists
	{
		int path_flow=INT_MAX;
		for(v=t;v!=s;v=parent[v])//backtracking fom dest to source using parent array
		{
			//flow to be added is min of all residual flows of vertices
			u=parent[v];
			path_flow=MIN(path_flow,residual[u][v]);
		}
		
		
		for(v=t;v!=s;v=parent[v])
		{
			u=parent[v];
			residual[u][v]-=path_flow;//reduce flow of vertex by pathflow
			residual[v][u]+=path_flow;//add pathflow to reverse edge
		}
		
		max_flow+=path_flow;//add path flow to max flow
	
	}
	
	return max_flow;
}



int main()
{
	FILE *fp; int V,i,j, **graph;
	
	if((fp=fopen("ford-ful.txt","r"))==NULL)
	{
		printf("File not found.\n");
		return 0;
	}
	
	fscanf(fp,"%d",&V);
	
	graph=(int **)malloc(V*sizeof(int *));
	for(i=0;i<V;i++)
		graph[i]=(int *)malloc(V*sizeof(int));
		
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			fscanf(fp,"%d",&graph[i][j]);
	
	printf("Max flow is: %d\n", fordful(graph,0,V-1,V));//find max flow from source zero to est V-1
	
	return 0;
}
