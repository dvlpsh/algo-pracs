#include<stdio.h>
#include<stdlib.h>


int isSafe(int **board, int x, int y, int N)
{
	int i,j;
	//column check
	//left diagonal check
	//right diagonal check
	
	//column check
	for(i=0;i<x;i++)
		if(board[i][y]==1)
			return 0;//not safe
			
	//left diagonal
	for(i=x-1,j=y-1;i>=0 && j>=0;i--,j--)
		if(board[i][j]==1)
			return 0;
			
	//right diagonal
	for(i=x-1,j=y+1;i>=0 && j<N;i--,j++)
		if(board[i][j]==1)
			return 0;
			
	return 1;
}


int placeQueen(int **board, int row, int N)
{
	for(int col=0;col<N;col++)//column count
	{
		board[row][col]=1;
		
		if(row<N-1 && isSafe(board,row,col,N)==1 && placeQueen(board,row+1,N)==1)
			return 1;
		
		if(row==N-1 && isSafe(board,row,col,N)==1)
			return 1;

		board[row][col]=0;
	}

	return 0;
}

void printSol(int **board, int N)
{
	int i,j;
	int sol=placeQueen(board,0,N);
	
	if(sol==1)
	{
		for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
				printf("%d ", board[i][j]);
			printf("\n");
		}
	}
}

int main()
{
	int **board, i;
	board=(int **)malloc(8*sizeof(int *));
	for(i=0;i<8;i++)
		board[i]=(int *)malloc(8*sizeof(int));
	
	printSol(board,8);
	return 0;
}
