// wytalkD.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 7
// April 2, 2025
//
// This program is the server side of my wytalk
//   program, it will open a socket and wait for
//   a client to connect with it and send simple
//   text back and forth.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "socketfun.h"

#define PORT 51100

int main(int argc, char *argv[]) {


  // Get Hostname
  char hostname[1024];
  hostname[1023] = '\0';
  gethostname(hostname, 1023);

  char buffer[1024];
  ssize_t bytesRead;


  int serverFd = serve_socket(hostname, PORT);
  if (serverFd == -1) {
    perror("Error: Could not create server socket");

    return 1;
  }

  int clientFd = accept_connection(serverFd);
  if (clientFd == -1) {
    perror("Error: Could not accept client connection");
    close(serverFd);

    return 1;
  }

  // Continuously look for input
  while (1) {

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

    // Print Message from Client
    printf("%s", buffer);
    fflush(stdout);

    if (fgets(buffer, 1024, stdin) == NULL) {
      break;  // Handle EOF (Ctrl+D)
    }

    if (write(clientFd, buffer, strlen(buffer)) == -1) {
      perror("Error writing to client");

      break;
    }
  }

  close(clientFd);
  close(serverFd);

  return 0;
}
