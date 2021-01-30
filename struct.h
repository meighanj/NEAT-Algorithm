#ifndef struct_h_
#define struct_h_

typedef struct
{
  float **values;
  float *pointer;
  int row;
  int col;
}
  Matrix;

typedef struct
{
	int **values;
	int *pointer;
	int row;
	int col;
}
	Board;


typedef struct
{
	Matrix *M;
	int layers;
}
	Weights;

#endif
