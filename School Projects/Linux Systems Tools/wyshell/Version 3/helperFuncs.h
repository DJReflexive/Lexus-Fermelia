// helperFuncs.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 10
// April 25, 2025
//
// Extra functions definitions
//   for this program.

#ifndef HELPER_FUNCS
#define HELPER_FUNCS

void freeUp(int argc, char *argv[]);
void freeFile(char **file);
void reapZombies(int sig);

void executeCommand(int argc, char *argv[], int background, int appendOut,
                    int pipesExist, char *inputFile, char *outputFile);

#endif
