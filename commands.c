#include "main.h"
#include "misc.h"
#include "commands.h"

int cd(char ** args){
  if ((strcmp(args[0], "cd")) || (args[1] == NULL) || (args[2]!=NULL)){
    printf("this shouldn't happen. usage: cd <directory>.\n");
    return -1;
  } else{
    char * path = strsep(&args[1], "\n");
    if (chdir(path)==-1)err();
  }
  return 0;
}
