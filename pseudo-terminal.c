#define _XOPEN_SOURCE 600
#define _DEFAULT_SOURCE
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int master_fd;
  // O_NOCTTY: not controlling terminal
  if ((master_fd = posix_openpt(O_RDWR)) == -1) {
    perror("Fail get pt master");
    exit(1);
  }
  if (grantpt(master_fd) == -1) {
    perror("Fail grantpt");
    exit(1);
  }
  if (unlockpt(master_fd)) {
    perror("Fail unlockpt");
    exit(1);
  }
  printf("Slave: %s\n", ptsname(master_fd));
  char read_but[1];
  size_t count;
  while (true) {
    if ((count = read(master_fd, read_but, 1) != -1)) {
      if (count == 1) {
        if (read_but[0] == '\r') {
          printf("Receive RET\n");
        } else {
          printf("Receive: %c\n", read_but[0]);
        }
        fflush(stdout);
      } else {
        printf("Slave disconnected\n");
        fflush(stdout);
        break;
      }
    } else {
      perror("Fail reading");
      exit(1);
    }
  }
  return 0;
}
