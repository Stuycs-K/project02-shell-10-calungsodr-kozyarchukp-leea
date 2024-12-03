#include "parse.h"
#include "misc.h"
#include <stdio.h>
int main(int argc, char *argv[]) {

  char * args[16];
  char buffer[256];
  getcwd(buffer, 256);
  printf("%s $ ", buffer);
  char line_buff[256];
  fgets(line_buff, 255, stdin);
  parse_args(line_buff, args);
  execvp(args[0], args);
  fflush(stdout);
}
