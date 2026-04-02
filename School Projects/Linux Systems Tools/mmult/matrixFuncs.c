// matrixFuncs.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 11
// May 11, 2025
//
// File that contains functions that assist
//   in matrix handling and calculations.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "matrix.h"

#define RC_BUFF_SIZE 8


// void setDimensionSize(char *buff, int buffSize, FILE *matrix, int *size)
// Parameters: buff - the string buffer
//             buffSize - size of the buffer
//             matrix - the file reading the matrix from
//             size - the dimension size to be set
// Return Value: void
//
// Gets dimension size by reading raw integer values from file
void setDimensionSize(char *buff, int buffSize, FILE *matrix, int *size) {
  fread(buff, buffSize, 1, matrix);
  memcpy(size, buff, sizeof(int32_t));
}



// void allocate(Matrix *m)
// Parameters: m - the matrix to be allocated
// Return Value: void
//
// Allocated memory to the given matrix
void allocate(Matrix *m) {
  // Check for valid dimension sizes
  if (m->rowCount <= 0 || m->columnCount <= 0) {
    fprintf(stderr, "Error: Matrices have invalid dimension sizes\n");
    exit(1);
  }

  // Allocate rows
  m->table = malloc(sizeof(double*) * m->rowCount);
  if (!m->table) {
    perror("Failed to allocate rows");
    exit(1);
  }

  for (int r = 0; r < m->rowCount; r++) {
    // Allocate columns
    m->table[r] = malloc(sizeof(double) * m->columnCount);
    if (!m->table[r]) {
      perror("Failed to allocate rows");
      exit(1);
    }
  }
}



// void setTableInfo(Matrix *m, FILE *fmatrix)
// Parameters: m - The internal reference matrix
//             fmatrix - The file containing the matrix info
// Return Value: void
//
// Read values from binary file and fill it into m
void setTableInfo(Matrix *m, FILE *fmatrix) {
  char rcBuff[RC_BUFF_SIZE];

  allocate(m);

  for (int r = 0; r < m->rowCount; r++) {
    // Fill in values
    for (int c = 0; c < m->columnCount; c++) {
      fread(rcBuff, RC_BUFF_SIZE, 1, fmatrix);
      memcpy(&m->table[r][c], rcBuff, sizeof(double));
    }
  }
}



// *worker(void *arg)
// Parameters: arg - passed arguments
// Return Value: void
//
// Invidual worker thread that locks
//   and manipulates data
void *worker(void *arg) {
  ThreadData *data = (ThreadData *)arg;

  while (1) {
    int row, col;

    // Lock and get the next (row, col) task
    pthread_mutex_lock(&data->coordMutex);
    if (data->nextRow >= data->mFinal.rowCount) {
      pthread_mutex_unlock(&data->coordMutex);
      break;
    }

    row = data->nextRow;
    col = data->nextCol;

    data->nextCol++;
    if (data->nextCol >= data->mFinal.columnCount) {
      data->nextCol = 0;
      data->nextRow++;
    }
    pthread_mutex_unlock(&data->coordMutex);

    // Compute mFinal[row][col]
    double sum = 0.0;
    for (int k = 0; k < data->m1.columnCount; k++) {
      sum += data->m1.table[row][k] * data->m2.table[k][col];
    }
    data->mFinal.table[row][col] = sum;

    // Signal main thread if a row is done
    if (col == data->mFinal.columnCount - 1) {
      pthread_mutex_lock(&data->writeMutex);
      data->elementsWritten += data->mFinal.columnCount;
      pthread_cond_signal(&data->writeCond);
      pthread_mutex_unlock(&data->writeMutex);
    }
  }

  pthread_exit(NULL);
}



// void freeMatrix(Matrix *m)
// Parameters: m - Matrix to be freed
// Return Value: void
//
// Deallocates matrix memory
void freeMatrix(Matrix *m) {
  for (int i = 0; i < m->rowCount; ++i) {
    free(m->table[i]);
  }

  free(m->table);
}



