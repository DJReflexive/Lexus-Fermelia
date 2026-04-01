// wytar.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 6
// March 6, 2025
//
// This files contains the source code
//   to my implementation of homework 6.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "helperFuncs.h"


int main(int argc, char *argv[]) {
  bool create = false, extract = false;
  bool fOptionFound = false, expectingArchive = false;

  char *archiveFile;
  int expectedArgs = 4;

  // Parse through args (just the first 3)
  for (int i = 1; i < expectedArgs; i++) {
    if (argv[i] == NULL) {
      perror("Usage: Must use either -c/-x, and -f with a valid filename");
      return 1;
    }


    if (strcmp(argv[i], "-c") == 0) {
      create = true;
    }
    if (strcmp(argv[i], "-x") == 0) {
      extract = true;
    }


    if (expectingArchive) {
      // If there is no filename following "-f" (not allowed)
      if (argv[i][0] == '-') {
        perror("Usage: Must provide valid filename after -f option");
        return 1;
      }

      archiveFile = argv[i];
      expectingArchive = false;
    }


    // -f, -cf, or -xf is passed
    if (strcmp(argv[i], "-f") == 0) {
      fOptionFound = true;
      expectingArchive = true;
    }
    else if (strcmp(argv[i], "-cf") == 0) {
      create = true;
      fOptionFound = true;
      expectingArchive = true;
      expectedArgs--; // Combining two arguments together
    }
    else if (strcmp(argv[i], "-xf") == 0) {
      extract = true;
      fOptionFound = true;
      expectingArchive = true;
      expectedArgs--; // Combining two arguments together
    }
  }


  // -c and -x are passed OR -c and -x are not passed OR -f is missing
  if ((create && extract) || (!create && !extract) || !fOptionFound) {
    perror("Usage: Must use either -c/-x, and -f with a valid filename");
    return 1;
  }

  // Begin processing now that preprocessing is done
  if (create) {
    char **files = argv + 4; // subarray containing files to be archived
    archiveFiles(archiveFile, files, argc-4);
  }
  if (extract) {
    extractFiles(archiveFile);
  }

  return 0;
}
