#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <termios.h>
#include <unistd.h>

int main() {
  struct termios termios;
  char buffer[10];
  if (tcgetattr(STDIN_FILENO, &termios) == -1) {
    perror("Fail to get termios");
    exit(1);
  }
  termios.c_lflag &= ~ECHO;
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios) == -1) {
    perror("Fail to set termios");
    exit(1);
  }
  printf("Please Enter something:");
  // scanf is not memory safe, it does not do bound checking
  int n;
  if ( (n = scanf("%s", buffer)) == EOF ){
    perror("Fail to read input");
    exit(1);
  }
  // printf("scanf return: %d\n", n);
  termios.c_lflag |= ECHO;
  if (tcsetattr(STDIN_FILENO, TCSANOW, &termios) == -1) {
    perror("Fail to set termios");
    exit(1);
  }
  printf("\nYou entered: %s\n", buffer);
  return 0;
}
