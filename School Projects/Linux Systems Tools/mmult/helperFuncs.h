// helperFuncs.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 11
// May 12, 2025
//
// Extra functions definitions
//   for this program.

#include "matrix.h"

#ifndef HELPER_FUNCS_H
#define HELPER_FUNCS_H


void setDimensionSize(char *buff, int buffSize, FILE *matrix, int *size);
void setTableInfo(Matrix *m, FILE *fmatrix);
void allocate(Matrix *m);
void *worker(void *arg);
void freeMatrix(Matrix *m);


#endif
