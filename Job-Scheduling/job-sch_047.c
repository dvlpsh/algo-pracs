#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int finish;
	int profit;	
	int id;
	
}job;


//mergesort

void merge(job *a, int l, int u)
{
	int m,i,j,k;
	static job b[100];
	if(l<u)
	{	
		m=(l+u)/2;
		merge(a,l,m);
		merge(a,m+1,u);
		
		
		for(i=l,j=m+1,k=l;i<=m && j<=u;)
		{
			if(a[i].profit>a[j].profit)
			{
				b[k++]=a[i];
				i++;
			}
			
			else
			{
				b[k++]=a[j];
				j++;
			}
		}
		
		while(i<=m)
		{
			b[k++]=a[i];
			i++;
		}
		
		while(j<=u)
		{
			b[k++]=a[j];
			j++;
		}
	
		for(k=l;k<=u;k++)
			a[k]=b[k];	
	}
}


void job_init_dead(job *jobarray, int n)
{
	int i;
	
	for(i=0;i<n;i++)
	{
		jobarray[i].id=i;
		//scanf("%d", &(jobarray[i].start));
		scanf("%d", &(jobarray[i].finish));
		scanf("%d", &(jobarray[i].profit));
	}
	//sorted jobs according to decreasing order of profits
	merge(jobarray,0,n-1);
}


void job_schdead(job *jobarray, int n)//n->no of jobs, when only deadline and profit given
{
	int i, k=jobarray[0].finish;//starting time=0
	
	job_init_dead(jobarray,n);
	
	printf("The sequence of jobs: %d",jobarray[0].id);
	for(i=1;i<n;i++)
	{
		if(jobarray[i].finish>=k)
		{
			printf(" %d",jobarray[i].id);
			k++;//each job takes one unit of time
		}	
	}
	
	printf("\n");
}



int main()
{
	job *jobarray; int n,i,j;
	scanf("%d", &n);
	jobarray=(job *)malloc(n*sizeof(job));
	
	/*for(i=0;i<n;i++)
		printf("job_profit:%d job_id:%d\n", jobarray[i].profit, jobarray[i].id);*/
	
	job_schdead(jobarray,n);
	
	return 0;
}
