// cleanup.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 10
// April 25, 2025
//
// Extra functions for cleanup

#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <stddef.h>

// void freeUp(int argc, char *argv[])
// Parameters: argc - number of arguments
//             argv - the argument vector
// Return Value: void
//
// Frees up memory when no longer needed
void freeUp(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
}

// void freeFile(char **file)
// Parameters: file - the file to freed
// Return Value: void
//
// Frees up file from memory when no longer needed
void freeFile(char **file) {
  if (file && *file) {
    free(*file);
    *file = NULL;
  }
}


// void reapZombies(int sig)
// Parameters: sig - ignored, required for the
//                   signal() function call
// Return Value: void
//
// Cleans up any present Zombies
void reapZombies(int sig) {
  while (waitpid(-1, NULL, WNOHANG) > 0);
}
