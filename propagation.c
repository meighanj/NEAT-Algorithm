#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operations.h"
#include "propagation.h"
#include "gameboard.h"

int phi(Board *Game_Board, Matrix *Input_Board, Matrix *W2, Matrix *W3, Matrix *W4, Matrix *B2, Matrix *B3, Matrix *B4, Board *Full_Board)

{
	Matrix Z2;
	declare_matrix(&Z2, W2->row, Game_Board->col);

	Matrix delta2;
	declare_matrix(&delta2, Z2.row, Z2.col); //delta2 same dimensions as Z2

	Matrix a2;
	declare_matrix(&a2, Z2.row, Z2.col); //same dimensions as Z2

	forward_Board(Game_Board, &a2, W2, &Z2, B2); //Game_Board, W2, B2 are already pointers

	printf("Matrix W2\n");
	print_matrix(W2);

	printf("Matrix A2\n");
	print_matrix(&a2);

	printf("Matrix Z2\n");
	print_matrix(&Z2);

	Matrix Z3;
	declare_matrix(&Z3, W3->row, Game_Board->col);

  Matrix delta3;
  declare_matrix(&delta3, Z3.row, Z3.col); //delta3 same dimensions as Z3

  Matrix a3;
  declare_matrix(&a3, Z3.row, Z3.col); //same dimensions as Z3

	forward_Matrix(&a2, &a3, W3, &Z3, B3);

	printf("Matrix W3\n");
	print_matrix(W3);

	printf("Matrix A3\n");
	print_matrix(&a3);

	printf("Matrix Z3\n");
	print_matrix(&Z3);



  Matrix Z4;
  declare_matrix(&Z4, W4->row, Game_Board->col);

  Matrix delta4;
  declare_matrix(&delta4, Z4.row, Z4.col); //delta4 same dimensions as 4

  Matrix a4;
  declare_matrix(&a4, Z4.row, Z4.col); //same dimensions as Z4

  forward_Matrix(&a3, &a4, W4, &Z4, B4);

	printf("Matrix W4\n");
	print_matrix(W4);

	printf("Matrix A4\n");
	print_matrix(&a4);

	printf("Matrix Z4\n");
	print_matrix(&Z4);

	return uncover(Game_Board, &a4, Full_Board);
}

void forward_Matrix(Matrix *a1, Matrix *a2, Matrix *W2, Matrix *Z2, Matrix *Bias)
{
	int i, j;	

	mat_mul(Z2, W2, a1);
	
	for(i=0;i<Z2->row;i++)
	{
		for(j=0;j<Z2->col;j++)
		{
			Z2->values[i][j] += Bias->values[i][0];
		}
	}
	sigmoid(a2,Z2);
}

void forward_Board(Board *b1, Matrix *a2, Matrix *W2, Matrix *Z2, Matrix *Bias)
{
	int i,j;
	board_mul(Z2,W2,b1);

	for(i=0;i<Z2->row;i++)
	{
		for(j=0;j<Z2->col;j++)
		{
			Z2->values[i][j] += Bias->values[i][0];
		}
	}
	sigmoid(a2,Z2);
}


int uncover(Board *Game_Board, Matrix *a4, Board *Full_Board)
{
	int i,j;
	int imax = 0;
	int jmax = 0;
	float max = Game_Board -> values[0][0];
	
	for(i=0;i<Game_Board->row;i++)
	{
		for(j=0;j<Game_Board->col;j++)
		{
			if(a4->values[i][j] > max)
			{
				max = a4->values[i][j];
				imax = i;
				jmax = j;
			}
		}
	}	
	
	while(Game_Board -> values[imax][jmax] != -1)
	{
		printf("Tile %d %d Already uncovered - Choosing Random Tile\n", imax, jmax);
		imax = rand() % Game_Board -> row;
		jmax = rand() % Game_Board -> col;
	}

	if(Full_Board -> values[imax][jmax] == -1)
	{
		printf("Tile %d %d contains a mine \n", imax, jmax);
		printf("Game Over\n");
		return 1;
	}
	else
	{
		printf("Uncovering Tile %d %d\n", imax, jmax);

		if(Full_Board -> values[imax][jmax] == 0)
			Open_Zeroes(Game_Board, Full_Board, imax, jmax);
		else
			Game_Board -> values[imax][jmax] = Full_Board -> values[imax][jmax];
		for(i=0;i<Game_Board->row;i++) {
			for(j=0;j<Game_Board->col;j++) {
				if(Game_Board -> values[i][j] < 0 && Full_Board -> values[i][j] != -1) /* uncovered tiles that aren't mines available */
					return 0;
			}	
		}	
		printf("All Tiles Uncovered, You Win!\n"); 
		return 1;
	}
}
