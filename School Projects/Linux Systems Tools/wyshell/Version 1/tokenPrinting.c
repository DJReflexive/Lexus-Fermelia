// tokenPrinting.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 8
// April 19, 2025
//
// This file includes multiple functions
//   that assist in interpreting tokens
//   and printing them. This file was meant
//   to be temporary and may not be in the
//   next iteration of this program

#include <stdio.h>
#include <stdlib.h>

#include "wyscanner.h"

int printRedirToken(int token) {
  if (token == REDIR_IN) {
    printf(" <\n");
    return 0;
  }
  if (token == REDIR_OUT) {
    printf(" >\n");
    return 0;
  }
  if (token == APPEND_OUT) {
    printf(" >>\n");
    return 0;
  }
  if (token == REDIR_ERR) {
    printf(" 2>\n");
    return 0;
  }
  if (token == APPEND_ERR) {
    printf(" 2>>\n");
    return 0;
  }
  if (token == REDIR_ERR_OUT) {
    printf(" 2>&1\n");
    return 0;
  }

  return 1;
}


int printDelimToken(int token) {
  if (token == SEMICOLON) {
    printf(" ;\n");
    return 0;
  }
  if (token == PIPE) {
    printf(" |\n");
    return 0;
  }
  if (token == AMP) {
    printf(" &\n");
    return 0;
  }

  return 1;
}


int handleEOL(int token) {
  if (token == EOL) {
    printf(" --: EOL\n");
  }
  else if (token == ERROR_CHAR) {
    printf("error character: %d\n", error_char);
    return 1;
  }
  else if (token == QUOTE_ERROR) {
    printf("quote error\n");
    return 1;
  }
  else if (token == SYSTEM_ERROR) {
    perror("system error");
    exit(EXIT_FAILURE);
  }

  return 0;
}
