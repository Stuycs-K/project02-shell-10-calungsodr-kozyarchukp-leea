#include "parse.h"
#include "misc.h"
#include "main.h"

int main(int argc, char *argv[]) {
  char ** args = prompt();
  printchars(args);
/*
  execvp(args[0], args);
  fflush(stdout);
  */
}


//prints cwd path and parses user input. returns array of args from stdin
char ** prompt(){
  char ** args = (char**)calloc(16, sizeof(char*));
  char buffer[256];
  getcwd(buffer, 256);
  printf("%s $ ", buffer);
  //i think fflush is supposed to go here maybe idk.........
  char * line_buff = (char*)calloc(256, sizeof(char));
  fgets(line_buff, 255, stdin);
  parse_args(line_buff, args);
  return args;
}
