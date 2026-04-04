#include <signal.h>
#include <sys/wait.h>
#include <stddef.h>

// Clean up Zombies
void reapZombies(int sig) {
  while (waitpid(-1, NULL, WNOHANG) > 0);
}
