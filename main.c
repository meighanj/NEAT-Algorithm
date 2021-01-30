#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<sys/time.h>
#include <time.h>
#include "operations.h"
#include "propagation.h"
#include "gameboard.h"

#define b_rows 8
#define b_columns 12
#define bombs 6
#define layers 3
#define print_stats 1 

void timer(struct timeval t1, struct timeval t2, double *elapsedTime)
{
  *elapsedTime = 0;
  *elapsedTime += (t2.tv_sec - t1.tv_sec) * 1000.0;    // seconds to milliseconds
  *elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
}

int main()
{
  int i;

	int *n_neurons;
	n_neurons = malloc((layers) * sizeof(int));
	
	for(i=0;i<layers;i++){
		if(i == 0)
			n_neurons[i] = b_rows;
		else if(i == layers - 1)
			n_neurons[i] = b_rows;
		else
			n_neurons[i] = (rand() % 16) + 5;
		printf("Layer %d has %d neurons \n", i, n_neurons[i]);
	}

	printf("Neurons declared \n");		

	int *w_rows, *w_cols;

	w_rows = malloc((layers - 1) * sizeof(int));
	w_cols = malloc((layers - 1) * sizeof(int));


	for(i=0;i<layers-1;i++){
		w_rows[i] = n_neurons[i+1];
		w_cols[i] = n_neurons[i];
		printf("Weight Matrix %d has dimensions (%d, %d)\n", i, w_rows[i], w_cols[i]);
	}
	printf("Weights rows and columns defined \n");
	
	Matrix *W;
	Matrix *B;
	
	W = malloc((layers - 1) * sizeof(Matrix));
	B = malloc((layers - 1) * sizeof(Matrix));

	for(i=0; i<layers-1;i++){
		declare_matrix(&W[i], w_rows[i], w_cols[i]);
		declare_matrix(&B[i], w_rows[i], 1);
		printf("Weight Matrix %d\n", i);
		init_weights(&W[i]);
		init_weights(&B[i]);
		print_matrix(&W[i]);
	}

Matrix *Z;
Matrix *a;

Z = malloc((layers - 1) * sizeof(Matrix));
a = malloc((layers - 1) * sizeof(Matrix));	

	
	Board Full_Board;
	declare_full(&Full_Board, b_rows, b_columns);
	init_board(&Full_Board, bombs);
	print_full(&Full_Board);

	/* This is a board the player sees */
	
	Board Game_Board;
	declare_game(&Game_Board, b_rows, b_columns);

	/* Declare as matrix so we can standardize between (-1,1) */

	Matrix Input_Board;
	declare_matrix(&Input_Board, b_rows, b_columns);
	standardize_matrix(&Game_Board, &Input_Board, b_rows, b_columns);
	if(print_stats == 1)
		print_matrix(&Input_Board);

//	print_game(&Game_Board); 

	i = 0;
	int j;
	int imax = 0;
	int jmax = 0;

	srand(time(0));

	while(1)
	{	
	
		if(i==0){/* first move take a random guess that doesn't contain a mine */


			imax = rand() % Full_Board.row;
			jmax = rand() % Full_Board.col;		

			while(Full_Board.values[imax][jmax] == - 1){
				imax = rand() % Full_Board.row;
				jmax = rand() % Full_Board.col;
			}
		
			if(Full_Board.values[imax][jmax] == 0)
				Open_Zeroes(&Game_Board, &Full_Board, imax, jmax);
			else
				Game_Board.values[imax][jmax] = Full_Board.values[imax][jmax];

			printf("First Move Uncovering Tile %d %d\n", imax, jmax);
		}

		else {
			for(j=0;j<layers-1;j++) {
				declare_matrix(&Z[j], n_neurons[j+1], b_columns);
				declare_matrix(&a[j], n_neurons[j+1], b_columns); 

				if(j == 0){

					if(print_stats == 1) {
						printf("Layer %d W has dimensions(%d,%d)\n", j, W[j].row, W[j].col);
						printf("Layer %d B has dimensions(%d,%d)\n", j, Input_Board.row, Input_Board.col);
						printf("Layer %d Z has dimensions(%d,%d)\n", j, n_neurons[j+1], b_columns);

					}

					forward_Matrix(&Input_Board, &a[j], &W[j], &Z[j], &B[j]); 
/*
					mat_mul(&Z[j], &W[j], &Input_Board);
					sigmoid(&a[j], &Z[j]);
*/
					free_matrix(&Z[j]);

				}

				else {

					if(print_stats == 1){
						printf("Layer %d W has dimensions(%d,%d)\n", j, W[j].row, W[j].col);
						printf("Layer %d a has dimensions(%d,%d)\n", j, a[j-1].row, a[j-1].col);
						printf("Layer %d Z has dimensions(%d,%d)\n", j, Z[j].row, Z[j].col);
					}

					forward_Matrix(&a[j-1], &a[j], &W[j], &Z[j], &B[j]);
/*					mat_mul(&Z[j], &W[j], &a[j-1]);
					sigmoid(&a[j], &Z[j]);
*/
					if(print_stats == 1) {
						printf("Layer %d Matrix W\n", j);
						print_matrix(&W[j]);
						printf("Layer %d Matrix a\n", j-1);
						print_matrix(&a[j-1]);
						printf("Layer %d Matrix Z\n", j);
						print_matrix(&Z[j]);
						printf("Layer %d Matrix a\n", j);
						print_matrix(&a[j]);						
					}

					free_matrix(&Z[j]);
					free_matrix(&a[j-1]);

				}
			}  
		} 

		if(i > 0){

			if(uncover(&Game_Board, &a[layers-2], &Full_Board) == 1) {	
				free_matrix(&a[layers-2]);
				break;
			}

			else
				free_matrix(&a[layers-2]);
		}
	
		standardize_matrix(&Game_Board, &Input_Board, b_rows, b_columns);
		print_game(&Game_Board);		

		i++;
	}

	for(i=0;i<layers-1;i++) {
		free_matrix(&W[i]);	free_matrix(&B[i]);	
	}
	return 0;
}

