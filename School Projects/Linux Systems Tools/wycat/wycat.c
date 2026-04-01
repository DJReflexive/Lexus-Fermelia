// wycat.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 4
// February 14, 2025
//
// This file is the source code of where my wycat will
// run from, the main file in which everything is run from.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// void processFile(FILE *file, char *filename)
// Parameters: pointer to the file to be processed
//   pointer to the file name that is being processed
//  Return Value: void
// This function will take a file and read blocks of
//   text from it, printing it out using stdout.
// Will return errors if there is an error writing
//   to stdout or if there is an error reading a file.
void processFile(FILE *file, char *filename) {

  // Process Blocks of Text
  const int BUFFER_SIZE = 4096;
  char buffer[BUFFER_SIZE];
  int bytesRead;
  do {
    bytesRead = fread(buffer, 1, BUFFER_SIZE, file);

    if (fwrite(buffer, 1, bytesRead, stdout) != bytesRead) {
      char errorMessage[] = "Error writing to stdout\n";
      fwrite(errorMessage, 1, sizeof(errorMessage), stderr);

      exit(1);
    }
  } while (bytesRead > 0);

  if (ferror(file)) {
    char errorMessage[] = "Error reading file: ";

    fwrite(errorMessage, 1, sizeof(errorMessage) - 1, stderr);
    fwrite(filename, 1, strlen(filename), stderr);
    fwrite("\n", 1, sizeof("\n"), stderr);
  }
}


int main(int argc, char *argv[]) {

  // If no arguments are passed
  if (argc == 1) {
    processFile(stdin, "stdin");
    return 0;
  }

  // Loop through Arguments
  for (int i = 1; i < argc; i++) {

    // If arg is a "-"
    if (strcmp(argv[i], "-") == 0) {
      processFile(stdin, "stdin");
      continue;
    }

    // Attempt to open file
    FILE *file = fopen(argv[i], "rb");
    if (!file) {
      char errorMessage[] = "Error: Cannot open file ";

      fwrite(errorMessage, 1, sizeof(errorMessage), stderr);
      fwrite(argv[i], 1, strlen(argv[i]), stderr);
      fwrite("\n", 1, sizeof("\n"), stderr);

      continue;
    }

    // File is open and is valid, now process it
    processFile(file, argv[i]);

    fclose(file);
  }

  return 0;
}
