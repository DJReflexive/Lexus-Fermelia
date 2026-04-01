// wytalkC.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 7
// April 2, 2025
//
// This program is the client side of my wytalk
//   program, it will connect with a server and
//   send simple text back and forth with it.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "socketfun.h"

#define PORT 51100

int main(int argc, char *argv[]) {
  char buffer[1024];
  ssize_t bytesRead;

  // Check for only 1 argument
  if (argc != 2) {
    perror("Usage: ./wytalkC <server-hostname>");

    return 1;
  }

  int clientFd = request_connection(argv[1], PORT);
  if (clientFd == -1) {
    perror("Error: Could not connect to server");

    return 1;
  }

  // Continuously look for input
  while (1) {

    if (fgets(buffer, 1024, stdin) == NULL) {
      break;  // Handle EOF (Ctrl+D)
    }

    // Send input to server
    if (write(clientFd, buffer, strlen(buffer)) == -1) {
      perror("Error writing to server");

      break;
    }

    int i = 0;
    while (i < 1024 - 1) {
      bytesRead = read(clientFd, &buffer[i], 1);

      if (bytesRead <= 0) {
        break;
      }

      if (buffer[i] == '\n') {
        i++;
        break;
      }

      i++;
    }

    buffer[i] = '\0';

    if (bytesRead <= 0) {
      break;
    }

    // Print message from Server
    printf("%s", buffer);
    fflush(stdout);
  }

  close(clientFd);

  return 0;
}
