#ifndef gameboard_h_
#define gameboard_h_

#include "struct.h"
#include "operations.h"

void print_full(Board *B);

void print_game(Board *B);

void declare_full(Board *B, int rows, int cols);

void declare_game(Board *B, int rows, int cols);

void init_board(Board *B, int Mines);

int count_mines(Board *B, int x, int y, int rows, int cols);

void Open_Zeroes(Board *G, Board *F, int x, int y);

#endif
