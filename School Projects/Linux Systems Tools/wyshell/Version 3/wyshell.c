// wyshell.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 10
// April 25, 2025
//
// This is the final version of my shell program
//   this current version parses input from the
//   user and interprets given token into a system
//   command that is executed by the system, properly
//   also handling redirections, pipes, and semicolons.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#include "wyscanner.h"
#include "helperFuncs.h"

#define MAX_ARGS 100
#define MAX_LINE_LENGTH 4096

int main() {
  int token;
  char line[MAX_LINE_LENGTH];
  char *argv[MAX_ARGS];
  int argc;
  int background;
  int stdinRedir;
  int pipesExist;

  char *inputFile = NULL;
  char *outputFile = NULL;
  int appendOutput = 0;

  // Read Lines Forever
  while (1) {
    printf("$> ");
    fflush(stdout);

    argc = 0;
    background = 0;
    stdinRedir = 0;
    pipesExist = 0;

    // Clean up Zombies (if any exist)
    signal(SIGCHLD, reapZombies);

    // Get the line
    if (fgets(line, sizeof(line), stdin) == NULL) {
      break;
    }

    // Detect any first token errors
    token = parse_line(line);
    if (token == SYSTEM_ERROR) {
      perror("SYSTEM_ERROR");
      exit(EXIT_FAILURE);
    }
    if (token == ERROR_CHAR) {
      fprintf(stderr, "ERROR_CHAR: %c\n", error_char);
      continue;
    }
    if (token == QUOTE_ERROR) {
      fprintf(stderr, "QUOTE_ERROR\n");
      continue;
    }
    if (token == PIPE) {
      fprintf(stderr, "Error: missing command before pipe\n");
      continue;
    }


    // Parsing the line
    while (token != EOL) {
      if (token == WORD) { // if word, append to argv
        if (argc < MAX_ARGS - 1) {
          argv[argc++] = strdup(lexeme);
        }
        else {
          fprintf(stderr, "Too many arguments\n");
          break;
        }
      }
      else if (token == AMP) { // if &
        background = 1;
      }
      else if (token == SEMICOLON) { // if ;
        argv[argc] = NULL;
        executeCommand(argc, argv, background, appendOutput,
                       pipesExist, inputFile, outputFile);

        argc = 0;
        inputFile = NULL;
        outputFile = NULL;
        token = parse_line(NULL); // skipping over ; token

        continue;
      }
      else if (token == PIPE) { // if |
        pipesExist = 1;

        if (argc < MAX_ARGS - 1) {
          argv[argc++] = strdup("|");
        }
        else {
          fprintf(stderr, "Too many arguments\n");
          break;
        }
      }
      else if (token == REDIR_IN || token == REDIR_OUT ||
               token == APPEND_OUT) { // if there is redirection
        if (token == REDIR_IN) {
          if (pipesExist) {
            fprintf(stderr, "Error: stdin already redirected by pipe\n");
            argc = 0;
            break;
          }

          if (stdinRedir) {
            fprintf(stderr, "Error: multiple stdin redirections\n");
            argc = 0;
            break;
          }

           stdinRedir = 1;
        }

        token = parse_line(NULL);
        if (token != WORD) {
          fprintf(stderr, "Error: expected file after redirection\n");
          argc = 0;
          break;
        }

        if (stdinRedir) {
          inputFile = strdup(lexeme);
        }
        else {
          outputFile = strdup(lexeme);
          appendOutput = (token == APPEND_OUT);
        }
      }
      else {
        fprintf(stderr, "Syntax Error\n");
        argc = 0;
        break;
      }

      token = parse_line(NULL); // Parse to next character
    }

    // Checks if line is empty
    if (argc == 0) {
      continue;
    }

    argv[argc] = NULL;
    executeCommand(argc, argv, background, appendOutput,
                   pipesExist, inputFile, outputFile);

    // Free Memory
    freeUp(argc, argv);
    freeFile(&inputFile);
    freeFile(&outputFile);
  }

  return 0;
}
