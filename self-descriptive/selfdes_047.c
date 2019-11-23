#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isSelfDesc(int *s, int len)
{
	int i,j,count;
	
	for(i=0;i<len;i++)
	{
		int dig=s[i];//digit at the ith index
		count=0;
		//traverse the entire number and check if dig appears i times
		for(j=0;j<len;j++)
		{
			int d=s[j];
			
			if(d==i)
				count++;
		}
		
		if(count==dig)
			continue;
		else
			return 0;
	}
	
	return 1;
}


int len(int n)
{
	int count=0;
	while(n>0)
	{
		n/=10;
		++count;
	}
	
	return count;
}


void toArray(int *s, int n)//return length
{
	int k=len(n)-1;
	while(n>0)
	{
		s[k--]=n%10;
		n/=10;
	}
}



int main()
{
	int i,j, length,res; int *s;
	s=(int *)malloc(10*sizeof(int));
	for(i=1;i<10000000;i++)
	{
		toArray(s,i);
		length=len(i);
		res=isSelfDesc(s,length);
		if(res==1)
			printf("%d\n", i);
	}
	return 0;
}
