#include "parse.h"
#include "misc.h"
#include "main.h"

int main(int argc, char *argv[]) {
  char * input = prompt();
  /*
  parse_args(line_buff, args);
  printchars(args);
  execvp(args[0], args);
  fflush(stdout);
  */
}


//prints cwd path and takes args. args are returned as a string
char * prompt(){
  char * args[16];
  char buffer[256];
  getcwd(buffer, 256);
  printf("%s $ ", buffer);
  //i think fflush is supposed to go here maybe idk.........
  char * line_buff = (char*)calloc(256, sizeof(char));
  fgets(line_buff, 255, stdin);
  return line_buff;
}
