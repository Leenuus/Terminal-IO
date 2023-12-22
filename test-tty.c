#include <stdio.h>
#include <unistd.h>

int main(){
  if ( isatty(STDOUT_FILENO) ){
    printf("It is a tty:%s\n", ttyname(STDOUT_FILENO));
  }else{
    perror("Not a tty");
  }
}
