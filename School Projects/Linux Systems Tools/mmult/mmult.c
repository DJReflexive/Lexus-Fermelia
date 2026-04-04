// mmult.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 11
// May 8, 2025
//
// My implementation of Homework 11.
//   This program performs a matrix
//   multiplication operation on two
//   input matrices given by two
//   files encoded to binary, and
//   outputs the result into an
//   encoded file in binary.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

#include "helperFuncs.h"
#include "matrix.h"

#define BUFF_SIZE 4

int main(int argc, char *argv[]) {

  // Valid proper usage
  if (argc < 4 || argc > 5) {
    fprintf(stderr, "Usage: ./mmult file1 file2 outputFile [numThreads]\n");
    return 1;
  }

  int numThreads = 0;
  if (argc == 5) { // get numThreads
    numThreads = atoi(argv[4]);

    if (numThreads <= 0) {
      fprintf(stderr, "Usage: argument [numThreads] must be a positive int\n");
      return 1;
    }
  }


  // Input Files
  FILE *fmatrix1 = fopen(argv[1], "rb");
  FILE *fmatrix2 = fopen(argv[2], "rb");
  if (fmatrix1 == NULL) {
    perror("Error: Failed to open 1st input file");
    return 1;
  }
  if (fmatrix2 == NULL) {
    perror("Error: Failed to open 2nd input file");
    return 1;
  }


  char buff[BUFF_SIZE];
  memset(buff, 0, BUFF_SIZE);

  // Gather row & column sizes, then set table content
  Matrix m1, m2;
  setDimensionSize(buff, BUFF_SIZE, fmatrix1, &m1.rowCount);
  setDimensionSize(buff, BUFF_SIZE, fmatrix1, &m1.columnCount);
  setDimensionSize(buff, BUFF_SIZE, fmatrix2, &m2.rowCount);
  setDimensionSize(buff, BUFF_SIZE, fmatrix2, &m2.columnCount);
  setTableInfo(&m1, fmatrix1);
  setTableInfo(&m2, fmatrix2);

  fclose(fmatrix1);
  fclose(fmatrix2);


  // Reject non-compatible matrices
  if (m1.columnCount != m2.rowCount) {
    fprintf(stderr, "Error: Passed invalid matrices (incompatible sizes)\n");
    return 1;
  }


  Matrix mFinal;
  mFinal.rowCount = m1.rowCount;
  mFinal.columnCount = m2.columnCount;
  allocate(&mFinal);

  // Write to output file
  FILE *outputFile = fopen(argv[3], "wb");
  if (outputFile == NULL) {
    perror("Error: Failed to create output file");
    return 1;
  }

  fwrite(&mFinal.rowCount, sizeof(int), 1, outputFile); // row count
  fwrite(&mFinal.columnCount, sizeof(int), 1, outputFile); // column count

  int elapsedTime;
  struct timeval startTime, endTime;

  if (numThreads <= 0) { // singleThread
    gettimeofday(&startTime, NULL);

    // Calculate Values
    for (int i=0; i < mFinal.rowCount; i++) {
      for (int j=0; j < mFinal.columnCount; j++) {
        mFinal.table[i][j] = 0.0; // initialize value

        for (int k=0; k < m1.columnCount; k++) {
          double elem1 = m1.table[i][k];
          double elem2 = m2.table[k][j];

          mFinal.table[i][j] += elem1 * elem2;
        }
      }
    }

    // write table content
    for (int r = 0; r < mFinal.rowCount; r++) {
      for (int c = 0; c < mFinal.columnCount; c++) {
        fwrite(&mFinal.table[r][c], sizeof(double), 1, outputFile);
      }
    }

    gettimeofday(&endTime, NULL);
  }
  else { // multiThread
    ThreadData data = {
      .m1 = m1,
      .m2 = m2,
      .mFinal = mFinal,
      .nextRow = 0,
      .nextCol = 0,
      .elementsWritten = 0,
      .totalElements = mFinal.rowCount * mFinal.columnCount
    };

    pthread_mutex_init(&data.coordMutex, NULL);
    pthread_mutex_init(&data.writeMutex, NULL);
    pthread_cond_init(&data.writeCond, NULL);

    gettimeofday(&startTime, NULL);

    pthread_t threads[numThreads];
    for (int i = 0; i < numThreads; i++) {
      pthread_create(&threads[i], NULL, worker, &data);
    }

    int writtenSoFar = 0;
    while (writtenSoFar < data.totalElements) {
      pthread_mutex_lock(&data.writeMutex);

      while (data.elementsWritten <= writtenSoFar) {
        pthread_cond_wait(&data.writeCond, &data.writeMutex);
      }

      // Write any complete rows that are ready
      int newElements = data.elementsWritten - writtenSoFar;
      int startRow = writtenSoFar / mFinal.columnCount;
      int endRow = (writtenSoFar + newElements) / mFinal.columnCount;

      for (int r = startRow; r < endRow; r++) {
        for (int c = 0; c < mFinal.columnCount; c++) {
          fwrite(&mFinal.table[r][c], sizeof(double), 1, outputFile);
        }
      }

      writtenSoFar += (endRow - startRow) * mFinal.columnCount;

      pthread_mutex_unlock(&data.writeMutex);
    }

    for (int i = 0; i < numThreads; i++) {
      pthread_join(threads[i], NULL);
    }

    gettimeofday(&endTime, NULL);

    pthread_mutex_destroy(&data.coordMutex);
    pthread_mutex_destroy(&data.writeMutex);
    pthread_cond_destroy(&data.writeCond);
  }

  elapsedTime = endTime.tv_sec - startTime.tv_sec;

  fclose(outputFile);


  // Terminal Output
  printf("Matrix sizes:\n");
  printf("  M: %d\n", mFinal.rowCount);
  printf("  N: %d\n", m1.columnCount);
  printf("  P: %d\n\n", mFinal.columnCount);
  printf("Worker threads: %d\n\n", numThreads);
  printf("Total time: %d seconds.\n\n", elapsedTime);


  // Cleanup
  freeMatrix(&m1);
  freeMatrix(&m2);
  freeMatrix(&mFinal);

  return 0;
}
