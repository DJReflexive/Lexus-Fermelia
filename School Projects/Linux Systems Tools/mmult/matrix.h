// matrix.h
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 11
// May 9, 2025
//
// Header file that contains two typedefs
//   used to assist in matrix calculations.
//   The Matrix type is a representation of
//   any given matrix. The ThreadData type
//   is used to assist in multithreaded processing.

#include <pthread.h>

#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
  int rowCount;
  int columnCount;

  double** table; // 2D table
} Matrix;




typedef struct {
  Matrix m1;
  Matrix m2;
  Matrix mFinal;

  int nextRow;
  int nextCol;

  pthread_mutex_t coordMutex;

  pthread_mutex_t writeMutex;
  pthread_cond_t writeCond;

  int elementsWritten;
  int totalElements;
} ThreadData;


#endif
