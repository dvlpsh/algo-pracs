#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct
{
	int totcap;//total capacity
	int rescap;//residual capacity
	int fill;//how much bin currently holds

}bin;

void bininit(bin *binarray, int binarrsize, int tcap)
{
	 int i;
	 
	 for(i=0;i<binarrsize;i++)
	 {
	 	binarray[i].totcap=tcap;
	 	binarray[i].rescap=tcap;
	 	binarray[i].fill=0;
	 }
}


int nextfit(bin *binarray, int binarrsize, int tcap, int *item, int itemarrsize)//return no of bins reqd,n is the size of array
{	
	int i=0,j=0,count=1;
	
	bininit(binarray,binarrsize,tcap);
	
	while(j<itemarrsize)
	{
		//if the jth item fits into the ith bin place it.
		if(binarray[i].rescap>0 && (binarray[i].fill+item[j]<=binarray[i].totcap))
		{
			binarray[i].rescap-=item[j];
			binarray[i].fill+=item[j];
			printf("if--> item %d in bin %d. Count=%d.\n", j, i,count);
			j++;
		}
		
		//else if the jth item doesnt fit into current bin, then place it into a new bin
		else
		{
			i++;
			binarray[i].rescap-=item[j];
			binarray[i].fill+=item[j];
			count++;
			printf("else--> item %d in bin %d. Count=%d.\n", j, i, count);
			j++;
		}
				
	}
	
	return count;
}

int firstfit(bin *binarray, int binarrsize, int tcap, int *item, int itemarrsize)//returns no of reqd bins
{
	int i=0,j=0,count=1,max=INT_MIN;
	
	bininit(binarray,binarrsize,tcap);
	
	while(j<itemarrsize)
	{
		for(i=0;i<binarrsize;)
		{
			//if the jth item fits into the ith bin place it.
			if(binarray[i].rescap>0 && (binarray[i].fill+item[j]<=binarray[i].totcap))
			{
				binarray[i].rescap-=item[j];
				binarray[i].fill+=item[j];
				printf("if--> item %d in bin %d. Count=%d.\n", j, i,count);
				max=i;
				j++;
				break;
			}
			
			//else if the jth item doesnt fit into current bin, then place it into a new bin
			else
			{
				i++;
				if(max>count)
					count=max;
			}
		}
	}
	
	return count;
}

int min(bin *binarray,int *bin_num, int count, int w)//w is current item weight, return 1 if possible, 0 otherwise
{
	int i, room, mincap=INT_MAX;
	
	for(i=1;i<=count;i++)
	{
		if(w<=binarray[i].rescap)
		{
			room=binarray[i].rescap-w;
			if(room < mincap)//leave least room
			{
				mincap=room;
				*bin_num=i;//important
			}
		}
	}
	
	//if donot fit into any bin
	if(*bin_num==-1)
		return 0;
	else
		return 1;
}


int bestfit(bin *binarray, int binarrsize, int tcap, int *item, int itemarrsize)
{
	int i=0,j=0,count=1,bin_num=-1,res,max=INT_MIN;
	
	bininit(binarray,binarrsize,tcap);
	
	
	while(j<itemarrsize)
	{
		//see in which bin it fits
		max=bin_num;
		bin_num=-1;
		res=min(binarray,&bin_num,count, item[j]);
		
		if(res==1)//possible;
		{
			binarray[bin_num].rescap-=item[j];
			binarray[bin_num].fill+=item[j];
			if(bin_num>count)
			{
				count=bin_num;
			}
			printf("if--> item %d in bin %d, rescap=%d. Count=%d.\n", j, bin_num,binarray[bin_num].rescap,count);
			//j++;//process the next item
		}
		
		else//cannot fit into any existing bin, open a new bin
		{
			count++;//increase no of bin
			binarray[count].rescap-=item[j];
			binarray[count].fill+=item[j];
			printf("else--> item %d in bin %d,rescap=%d. Count=%d.\n", j, count,binarray[count].rescap, count);
			//j++;
		}
		j++;
	}

	return count;
}



int main()
{
	int i;
	bin *binarray; 
	int binarrsize,tcap, *item, itemarrsize;
	
	printf("Enter binarray size:");
	scanf("%d", &binarrsize);
	printf("Enter itemarray size:");
	scanf("%d", &itemarrsize);
	printf("Enter total capacity:");
	scanf("%d", &tcap);	
	
	binarray=(bin *)malloc(binarrsize*sizeof(bin));
	
	item=(int *)malloc(itemarrsize*sizeof(int));
	for(i=0;i<itemarrsize;i++)
		scanf("%d", &item[i]);	
	
	printf("%d bins required.\n", bestfit(binarray,binarrsize,tcap,item,itemarrsize));

	return 0;
}
