#ifndef propagation_h_
#define propagation_h_

int phi(Board *Game_Board, Matrix *Input_Board, Matrix *W2, Matrix *W3, Matrix *W4, Matrix *Bias2, Matrix *Bias3, Matrix *Bias4, Board *Full_Board);

void forward_Matrix(Matrix *a1, Matrix *a2, Matrix *W2, Matrix *Z2, Matrix *Bias);

void forward_Board(Board *b1, Matrix *a2, Matrix *W2, Matrix *Z2, Matrix *Bias);

int uncover(Board *Game_Board, Matrix *a4, Board *Full_Board);

#endif
