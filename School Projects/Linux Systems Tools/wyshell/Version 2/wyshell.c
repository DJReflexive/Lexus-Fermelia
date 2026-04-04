// wyshell.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 9
// April 20, 2025
//
// This is the second version of my shell program
//   this current version parses input from the
//   user and interprets given token into a system
//   command that is executed by the system.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
  int pipedIn;

  // Clean up Zombies
  signal(SIGCHLD, reapZombies);

  while (1) {
    printf("$> ");
    fflush(stdout);

    argc = 0;
    background = 0;
    stdinRedir = 0;
    pipedIn = 0;

    if (fgets(line, sizeof(line), stdin) == NULL) {
      break; // EOF or error
    }

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
      fprintf(stderr, "Syntax Error: missing command before pipe\n");
      continue;
    }

    // Parsing
    while (token != EOL) {
      if (token == WORD) {
        if (argc < MAX_ARGS - 1) {
          argv[argc++] = strdup(lexeme);
        }
        else {
          fprintf(stderr, "Too many arguments\n");
          break;
        }
      }
      else if (token == AMP) {
        background = 1;
      }
      else if (token == SEMICOLON) {
        break;
      }
      else if (token == PIPE) {
        pipedIn = 1;
      }
      else if (token == REDIR_IN || token == REDIR_OUT ||
               token == APPEND_OUT) {
        if (token == REDIR_IN) {
          if (pipedIn) {
            fprintf(stderr, "Syntax Error: stdin already redirected by pipe\n");
            argc = 0;
            break;
          }

          if (stdinRedir) {
            fprintf(stderr, "Syntax Error: multiple stdin redirections\n");
            argc = 0;
            break;
          }

           stdinRedir = 1;
        }

        token = parse_line(NULL);
        if (token != WORD) {
          fprintf(stderr, "Syntax Error: expected file after redirection\n");
          argc = 0;
          break;
        }
      }
      else {
        fprintf(stderr, "Syntax error\n");
        argc = 0;
        break;
      }

      token = parse_line(NULL); // Continue parsing the current line
    }

    argv[argc] = NULL;

    if (argc == 0) {
      continue;
    }

    pid_t pid = fork();
    if (pid == 0) {
      // Child process
      execvp(argv[0], argv);
      perror("execvp failed");
      exit(EXIT_FAILURE);
    }
    else if (pid > 0) {
      // Parent process
      if (!background) {
        waitpid(pid, NULL, 0);
      }
    }
    else {
      perror("fork failed");
    }

    // Free the duplicated strings
    for (int i = 0; i < argc; i++) {
      free(argv[i]);
    }
  }

  return 0;
}

