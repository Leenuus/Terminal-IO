#include <asm-generic/ioctls.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

struct winsize o_winsize;

void intr_handler(int sig) { 
  ioctl(STDOUT_FILENO, TIOCSWINSZ, &o_winsize); 
  exit(0);
}

int main(int argc, char **argv) {

  struct sigaction sa;
  sa.sa_handler = intr_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sigaction(SIGINT, &sa, NULL);

  struct winsize winsize;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize);
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &o_winsize);
  if (argc >= 2) {
    winsize.ws_col = atoi(argv[1]);
    if (argc == 3) {
      winsize.ws_row = atoi(argv[2]);
    }
    ioctl(STDOUT_FILENO, TIOCSWINSZ, &winsize);
  }
  while (true) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize);
    printf("col: %d, row: %d\n", winsize.ws_col, winsize.ws_row);
    sleep(1);
  }
}
