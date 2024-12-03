#include "main.h"
#include "misc.h"
#include "commands.h"

int cd(char ** args){
  if ((!equals(args[0], "cd")) || (args[2] != NULL)){
    printf("this shouldn't happen. either the args don't specify that this is a cd command, or there are too many args.");
  } else{
    char * path = genPath(args[1]);
    chdir(path);
  }
}

char * genPath(char * extra){
  char * path = (char*)calloc(256, sizeof(char));
  int PATH_SIZE = 256*sizeof(char);
  path = getcwd(path, PATH_SIZE);
  path = strcat(path, extra);
  return path;
}
