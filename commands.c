#include "main.h"
#include "misc.h"
#include "commands.h"

int cd(char ** args){
  printf("cd time\n");
  if ((!strcmp(args[0], "cd")) || (args[1] == NULL) || (args[2] != NULL)){
    printf("this shouldn't happen. either the args don't specify that this is a cd command, there are too little args, or there are too many args.\n");
  } else{
    char * path = genPath(args[1]);
    chdir(path);
  }
}

char * genPath(char * extra){
  printf("hi\n");
  char * path = (char*)calloc(256, sizeof(char));
  int PATH_SIZE = 256*sizeof(char);
  path = getcwd(path, PATH_SIZE);
  path = strcat(path, extra);
  printf("path is %s\n", path);
  return path;
}
