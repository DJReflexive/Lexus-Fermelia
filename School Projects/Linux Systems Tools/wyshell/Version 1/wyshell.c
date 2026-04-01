// wyshell.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 9
// April 20, 2025
//
// This is the first version of my shell program
//   this current version parses input from the
//   user and interprets given tokens.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wyscanner.h"
#include "helperFuncs.h"

#define MAX_LINE_LENGTH 4096

int main(int argc, char *argv[]) {
  char line[MAX_LINE_LENGTH];

  // Main Loop
  while (1) {
    printf("$> ");
    fflush(stdout);

    // Read input
    if (fgets(line, sizeof(line), stdin) == NULL) {
      break; // EOF or error
    }

    int token;
    int firstWord = 1;
    int hasIn = 0, hasOut = 0, hasErr = 0;
    int awaitingFilename = 0;

    token = parse_line(line);

    // Parse Line
    while (token >= 0 && token != EOL) {
      if (token == WORD) {

        char *word = strdup(lexeme);
        if (!word) {
          perror("system error");
          return 1;
        }

        if (awaitingFilename) {
          printf(" --: %s\n", word);
          awaitingFilename = 0;
        }
        else if (firstWord) {
          printf(":--: %s\n", word);
          firstWord = 0;
        }
        else {
          printf(" --: %s\n", word);
        }

        free(word);
      }
      else if (token == REDIR_IN || token == REDIR_OUT ||
               token == APPEND_OUT || token == REDIR_ERR ||
               token == APPEND_ERR || token == REDIR_ERR_OUT) {

        // Check for duplicate redirections
        if ((token == REDIR_IN && hasIn) ||
           ((token == REDIR_OUT || token == APPEND_OUT) && hasOut) ||
           ((token == REDIR_ERR || token == APPEND_ERR ||
             token == REDIR_ERR_OUT) && hasErr)) {

          if (token == REDIR_IN) {
            printf("Ambiguous input redirection\n");
          }
          else {
            printf("Ambiguous output redirection\n");
          }

          // skip the rest
          while ((token = parse_line(NULL)) != EOL && token > 0);

          break;
        }

        // Mark redirection presence
        if (token == REDIR_IN) {
          hasIn = 1;
        }
        if (token == REDIR_OUT || token == APPEND_OUT) {
          hasOut = 1;
        }
        if (token == REDIR_ERR || token == APPEND_ERR ||
            token == REDIR_ERR_OUT) {
          hasErr = 1;
        }

        if (printRedirToken(token)) { // returns 1 if a token prints
          break;
        }
        else {
          awaitingFilename = 1;
        }
      }
      else if (token == SEMICOLON || token == PIPE || token == AMP) {
        if (printDelimToken(token)) { // returns 1 if a token prints
          break;
        }
        else {
          firstWord = 1;
          awaitingFilename = 0;
        }
      }

      token = parse_line(NULL);
    }

    if (handleEOL(token)) {
      continue;
    }

    if (awaitingFilename) {
      printf("syntax error near unexpected token 'newline'\n");
      continue;
    }
  }

  return 0;
}

