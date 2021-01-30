#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operations.h"
#include "struct.h"

void print_matrix(Matrix *A)
{
  int i, j;

  for(i=0;i<A->row;i++)
  {
		printf("%d\t", i);
    for(j=0;j<A->col;j++)
    {
	   	printf("%s%.3f ", A->values[i][j] < 0 ? "" : " ", A->values[i][j]);
    }
    printf("\n");
  }
}

void copy_matrix(float **dest, float **src, int n, int m)
{
	int i, j;

	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			dest[i][j] = src[i][j];
		}
	}

}

void declare_matrix(Matrix *A, int nrow, int ncol)
{
  int i, j;

  A->row = nrow;
  A->col = ncol;

  A->values = malloc(sizeof(float *) * nrow);
  A->pointer = malloc(sizeof(float) * nrow * ncol);
  for(i=0;i<nrow;i++)
    A->values[i] = &A->pointer[i*ncol];

  for(i=0;i<nrow;i++)
  {
    for(j=0;j<ncol;j++)
    {
      A->values[i][j] = 0;
    }
  }
}

void standardize_matrix(Board *A, Matrix *B, int nrow, int ncol)
{
	int i, j;
	for(i=0;i<nrow;i++){
		for(j=0;j<ncol;j++){
			B->values[i][j] = A -> values[i][j] / 9.0;
		}
	}

}

void free_matrix(Matrix *A)
{
	free(A->pointer);
	free(A->values);
}

void init_weights(Matrix *A)
{
  int i, j;

  for(i=0;i<A->row;i++)
  {
    for(j=0;j<A->col;j++)
      A->values[i][j] = 1 - (2*(float)rand()/RAND_MAX);
  }
}

void mat_mul(Matrix *C, Matrix *A, Matrix *B)
{
  int i, j, k;
	if(A -> col != B -> row)
		printf("ERROR mat_mul: A -> col != B -> row %d != %d\n", A -> col, B -> row);
	if(C -> row != A -> row)
		printf("ERROR mat_mul: A -> row != C -> row %d != %d\n", A -> row, C -> row);
	if(C -> col != B -> col)
		printf("ERROR mat_mul: B -> col != C -> col %d != %d\n", B -> col, C -> col);

  for(i=0;i<A->row;i++)
  {
    for(j=0;j<B->col;j++)
    {
      C->values[i][j] = 0;
      for(k=0;k<A->col;k++)
      {
        C->values[i][j] += A->values[i][k] * B->values[k][j];
      }
    }
  }
}

void board_mul(Matrix *C, Matrix *A, Board *B)
{
	int i,j,k;
	
	for(i=0;i<A->row;i++)
	{	
		for(j=0;j<B->col;j++)
		{
			C->values[i][j] = 0;
			for(k=0;k<A->col;k++)
			{
				C->values[i][j] += A->values[i][k] * B->values[k][j];
			}
		}
	}
}

void left_trans_mult(Matrix *C, Matrix *A, Matrix *B)
{
  int i, j, k;

  for(i=0;i<A->col;i++)
  {
    for(j=0;j<B->col;j++)
    {
      C->values[i][j] = 0;
      for(k=0;k<A->row;k++)
      {
        C->values[i][j] += A->values[k][i] * B->values[k][j];
      }
    }
  }
}

void right_trans_mult(Matrix *C, Matrix *A, Matrix *B)
{
  int i, j, k;

  for(i=0;i<A->row;i++)
  {
    for(j=0;j<B->row;j++)
    {
      C->values[i][j] = 0;
      for(k=0;k<A->col;k++)
      {
        C->values[i][j] += A->values[i][k] * B->values[j][k];
      }
    }
  }
}

void sigmoid(Matrix *next, Matrix *old)
{
  int i, j;

  for(i=0;i<old->row;i++)
  {
    for(j=0;j<old->col;j++)
    {
      next->values[i][j] = 1/(1+exp(-old->values[i][j]));
    }
  }
}

void sigmoid_prime(Matrix *A)
{
  float sigma;
  int i, j;

  for(i=0;i<A->row;i++)
  {
    for(j=0;j<A->col;j++)
    {
      sigma = 1/(1+exp(-A->values[i][j]));

      A->values[i][j] = sigma*(1-sigma);
    }
  }
}

void dot_product(Matrix *A, Matrix *B)
{
  int i, j;

  for(i=0;i<A->row;i++)
  {
    for(j=0;j<A->col;j++)
    {
      A->values[i][j] *= B->values[i][j];
    }
  }
}

void output(Matrix *a4, int *Y, int *correct, int *total)
{
  int i, j;
  float max;
  int position;


  for(i=0;i<a4->col;i++)
  {
		*total = *total + 1;
    max = a4->values[0][i];
    position = 0;
    for(j=1;j<a4->row;j++)
    {
      if(max < a4->values[j][i])
      {
        max = a4->values[j][i];
        position = j;
      }
    }
		if(position == Y[i])
			*correct = *correct + 1;

  }
}

