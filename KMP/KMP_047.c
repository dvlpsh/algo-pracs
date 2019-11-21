#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void computeLPS(int lps[],int m,char *pat)//m=length of lps array
{
	int j,i;

	j=0;
	i=j+1;
	lps[0]=0;

	while(i<m)
	{
		if(pat[j]==pat[i])
		{
			lps[i]=j+1;
			i++;
			j++;
		}
		
		else //if pat[j]!=pat[i]
		{
			if(j!=0)
				j=lps[j-1];
			
			else//if j==0
			{
				lps[i]=0;
				i++;
			}
		}
	}
}


void KMPsearch(char *str, char *pat)
{
	int n=strlen(str);
	int m=strlen(pat);
	int *lps;
	
	lps=(int *)malloc(m*sizeof(int));
	
	computeLPS(lps,m,pat);
	
	int i=0,j=0;
	
	while(i<n)
	{
		if(str[i]==pat[j])
		{
			i++;
			j++;
		}
		
		else if(i<n && str[i]!=pat[j])
		{
			if(j!=0)
				j=lps[j-1];
			else
				i++;
		}
		
		if(j==m)
		{
			printf("Pattern found at index %d\n",i-j);
			j=lps[j-1];
		}
	}
}



int main()
{
	char pat[20],str[20];
	FILE *fp;
	
	if((fp=fopen("KMP.txt","r"))==NULL)
	{
		printf("File not found!");
		return 0;
	}
	
	fscanf(fp,"%[^\n]%*c", str);
	fscanf(fp,"%[^\n]%*c", pat);
	
	KMPsearch(str,pat);
	
	return 0;
}
