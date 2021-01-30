#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include "struct.h"
#include "operations.h"
#include "gameboard.h"

void print_full(Board *B)
{
	int i, j;
	printf("\n");

	for(i=0;i<B->row;i++)
	{
		printf("%d\t",i);
		for(j=0;j<B->col;j++)
		{
			if(B->values[i][j] == -1)
			{
				printf(" \033[1;31m\u25CF\033[0m ");
			}
			else if(B->values[i][j] == 0)
				printf("   ");
			else if(B->values[i][j] == 1)
				printf(" \033[0;36m%d\033[0m ", 1);
			else if(B->values[i][j] == 2)
				printf(" \033[0;32m%d\033[0m ", 2);
			else if(B->values[i][j] == 3)
				printf(" \033[0;31m%d\033[0m ", 3);
			else if(B->values[i][j] == 4)
				printf(" \033[0;35m%d\033[0m ", 4);
			else if(B->values[i][j] == 5)
				printf(" \033[0;33m%d\033[0m ", 5);
			else
				printf(" \033[0;32m%d\033[0m ", B-> values[i][j]);
		
		}
		printf("\n");	
	}
}

void print_game(Board *B)
{
	int i,j;
	printf("\n");
	for(i=0;i<B->row;i++)
	{
		printf("%d\t", i);
		for(j=0;j<B->col;j++)
		{
			if(B->values[i][j] == -1)
				printf(" \u23F9 ");

			else if(B->values[i][j] == 0)
				printf("   ");

			else if(B->values[i][j] == 1)
				printf(" \033[0;36m%d\033[0m ", 1);

			else if(B->values[i][j] == 2)
				printf(" \033[0;36m%d\033[0m ", 2);

			else if(B->values[i][j] == 3)
				printf(" \033[0;36m%d\033[0m ", 3);

			else if(B->values[i][j] == 4)
				printf(" \033[0;36m%d\033[0m ", 4);

			else if(B->values[i][j] == 5)
				printf(" \033[0;36m%d\033[0m ", 5);
			else 
				printf(" %d ", B-> values[i][j]);
		}
		printf("\n");	
	}
}


void declare_full(Board *B, int rows, int cols)
{
	int i,j;
	
	B -> row = rows;
	B -> col = cols; 

	B -> values = malloc(rows * sizeof(int *));
	B -> pointer = malloc(sizeof(int) * rows * cols);
	for(i=0;i<rows;i++)
		B->values[i] = &B->pointer[i*cols];

	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)	
		{
			B -> values[i][j] = 0;
		}
	}
}

void declare_game(Board *B, int rows, int cols)
{
	int i,j;
		
	B -> row = rows;
	B -> col = cols;
	
	B-> values = malloc(rows * sizeof(int *));
	B -> pointer = malloc(sizeof(int) * rows * cols);
	for(i=0;i<rows;i++)
		B->values[i] = &B->pointer[i*cols];

	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{	
			B -> values[i][j] = -1;
		}
	}		
}

void init_board(Board *B, int Mines)
{
	int i, j;
	int r, c;

	for(i=0;i<Mines;i++)
	{
		r = rand() % B -> row;
		c = rand() % B -> col;

		while(B -> values[r][c] == -1)
		{
			r = rand() % B -> row;
			c = rand() % B -> col;
		}

		B -> values[r][c] = -1;
	}

	for(i=0;i<B -> row;i++)
	{
		for(j=0;j<B -> col; j++)
		{
			if (B -> values[i][j] != -1)
				B -> values [i][j] =  count_mines(B, i, j, B -> row, B -> col);
		}
	}
}

int count_mines(Board *B, int x, int y, int rows, int cols)
{
	int count;
	count = 0;	

	if(x-1 >= 0 && y-1 >= 0) 
	{
		if(B -> values[x-1][y-1] == -1)
			count++;
	}
	if(x-1 >= 0)
	{
		if(B -> values[x-1][y] == -1)
			count++;

		if(y+1 < cols)
		{
			if(B -> values[x-1][y+1] == -1)
				count++;
		}
	}

	if(y-1 >= 0)
	{
		if(B -> values[x][y-1] == -1)
			count++;
		if(x+1 < rows)
		{
			if(B -> values[x+1][y-1] == -1)
				count++;	
		}			
	}	
	
	if(x+1 < rows) 
	{
		if(B-> values[x+1][y] == -1)
			count++;
	}

	if(y+1 < cols)
	{
		if(B -> values[x][y+1] == -1)
			count++;	
	}	

	if(x+1 < rows && y+1 < cols)	
	{
		if(B -> values[x+1][y+1] == -1)
			count++;
	}
	
	return count;
}

void Open_Zeroes(Board *G, Board *F, int x, int y)
{
	int rows, cols;
	
	rows = G -> row;
	cols = G -> col;	

	G -> values[x][y] = F -> values[x][y];

	if(x > 0 && y > 0)
	{
		if(G -> values[x-1][y-1] == -1 && F -> values[x-1][y-1] == 0)
			Open_Zeroes(G, F, x-1, y-1);
		else	
			G -> values[x-1][y-1] = F -> values[x-1][y-1];
	}
	
	if(x > 0)
	{
		if(G -> values[x-1][y] == -1 && F -> values[x-1][y] == 0)
			Open_Zeroes(G,F, x-1, y);
		else
			G -> values[x-1][y] = F -> values[x-1][y];
	
		if(y+1 < cols)
		{
			if(G -> values[x-1][y+1] == -1 && F -> values[x-1][y] == 0)
				Open_Zeroes(G, F, x-1, y+1);
			else
				G -> values[x-1][y+1] = F -> values[x-1][y+1];
		}
	}

	if(y > 0)
	{
		if(G -> values[x][y-1] == -1 && F -> values[x][y-1] == 0)
			Open_Zeroes(G, F, x, y-1);
		else
			G -> values[x][y-1] = F -> values[x][y-1];		

		if(x+1 < rows)
		{
			if(G -> values[x+1][y-1] == -1 && F -> values[x+1][y-1] == 0)
				Open_Zeroes(G, F, x+1, y-1);
			else
				G -> values[x+1][y-1] = F -> values[x+1][y-1];
		}
	}
	
	if(x+1 < rows)
	{
		if(G -> values[x+1][y] == -1 && F -> values[x+1][y] == 0)
			Open_Zeroes(G, F, x+1, y);
		else
			G -> values[x+1][y] = F -> values[x+1][y];
	}		

	if(y+1 < cols)
	{
		if(G -> values[x][y+1] == -1 && F -> values[x][y+1] == 0)
			Open_Zeroes(G, F, x, y+1);
		else
			G -> values[x][y+1] = F -> values[x][y+1];
	}	

	if(x+1 < rows && y+1 < cols)
	{
		if(G -> values[x+1][y+1] == -1 && F -> values[x+1][y+1] == 0)
			Open_Zeroes(G, F, x+1, y+1);
		else
			G -> values[x+1][y+1] = F -> values[x+1][y+1];
	}
}

