// execution.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 10
// April 27, 2025
//
// This file contains functions that
//   assist in command execution.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#include "helperFuncs.h"

#define MAX_ARGS 100

// void executeCommand(int argc, char *argv[], int background, int appendOut
//                     char *inputFile, char *outputFile)
// Parameters: argc - argument count
//             argv - argument vector
//             background - decides whether to be processed in the background
//             appendOut - decides whether outputFiles are appended or not
//             inputFile - (can be NULL)
//             outputFile - (can be NULL)
// Return Value: void
//
// Executes the given command
void executeCommand(int argc, char *argv[], int background, int appendOut,
                    int pipesExist, char *inputFile, char *outputFile) {
  if (pipesExist) {
    printf("DEBUG: Executing command with pipes\n");

    /*
     *  ChatGPT: Add your code here
     */
    int numPipes = 0;
    for (int i = 0; i < argc; i++) {
      if (strcmp(argv[i], "|") == 0) {
        numPipes++;
      }
    }

    int pipefds[2 * numPipes];
    for (int i = 0; i < numPipes; i++) {
      if (pipe(pipefds + i * 2) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
      }
    }

    int cmdIndex = 0;
    int pipeIndex = 0;
    pid_t pid;
    int status;

    while (cmdIndex < argc) {
      // Find end of current command
      int cmdEnd = cmdIndex;
      while (cmdEnd < argc && strcmp(argv[cmdEnd], "|") != 0) {
        cmdEnd++;
      }

      // Prepare arguments for execvp
      char *cmdArgs[MAX_ARGS];
      int k = 0;
      for (int i = cmdIndex; i < cmdEnd; i++) {
        cmdArgs[k++] = argv[i];
      }
      cmdArgs[k] = NULL;

      pid = fork();
      if (pid == 0) {
        // Child

        // If not the first command, read from previous pipe
        if (pipeIndex != 0) {
          if (dup2(pipefds[(pipeIndex - 1) * 2], STDIN_FILENO) < 0) {
            perror("dup2 stdin");
            exit(EXIT_FAILURE);
          }
        }

        // If not the last command, write to next pipe
        if (cmdEnd < argc) {
          if (dup2(pipefds[pipeIndex * 2 + 1], STDOUT_FILENO) < 0) {
            perror("dup2 stdout");
            exit(EXIT_FAILURE);
          }
        }

        // Close all pipe fds
        for (int i = 0; i < 2 * numPipes; i++) {
          close(pipefds[i]);
        }

        execvp(cmdArgs[0], cmdArgs);
        perror("execvp");
        exit(EXIT_FAILURE);
      }
      else if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
      }

      cmdIndex = cmdEnd + 1;
      pipeIndex++;
    }

    // Parent closes all pipe fds
    for (int i = 0; i < 2 * numPipes; i++) {
      close(pipefds[i]);
    }

    // Wait for all children
    while (wait(&status) > 0);

  }
  else {
    printf("DEBUG: Executing command without pipes\n");

    pid_t pid = fork();

    // Child process
    if (pid == 0) {
      if (inputFile) {
        int fd = open(inputFile, O_RDONLY);

        if (fd < 0) {
          perror("open input file");
          exit(EXIT_FAILURE);
        }

        dup2(fd, STDIN_FILENO);
        close(fd);
      }

      if (outputFile) {
        int flags = O_WRONLY | O_CREAT | (appendOut ? O_APPEND : O_TRUNC);
        int fd = open(outputFile, flags, 0644);

        if (fd < 0) {
          perror("open output file");
          exit(EXIT_FAILURE);
        }

        dup2(fd, STDOUT_FILENO);
        close(fd);
      }

      execvp(argv[0], argv);
      perror("execvp failed");
      exit(EXIT_FAILURE);
    }
    // Parent process
    else if (pid > 0) {
      if (!background) {
        waitpid(pid, NULL, 0);
      }
    }
    else {
      perror("Error: fork failed");
    }
  }
}
