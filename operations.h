#ifndef operations_h_
#define operations_h_

#include "struct.h"

void print_matrix(Matrix *A);

void standardize_matrix(Board *A, Matrix *B, int nrow, int ncol);

void copy_matrix(float **dest, float **src, int n, int m);

void declare_matrix(Matrix *A, int nrow, int ncol);

void free_matrix(Matrix *A);

void print_letter(float **X, int *ytemp, int xrow, int width);

void init_weights(Matrix *A);

void mat_mul(Matrix *C, Matrix *A, Matrix *B);

void board_mul(Matrix *C, Matrix *A, Board *B);

void left_trans_mult(Matrix *C, Matrix *A, Matrix *B);

void right_trans_mult(Matrix *C, Matrix *A, Matrix *B);

void sigmoid(Matrix *next, Matrix *old);

void sigmoid_prime(Matrix *A);

void dot_product(Matrix *A, Matrix *B);

void output(Matrix *a4, int *Y, int *correct, int *total);


#endif
