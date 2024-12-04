#include "parse.h"
#include "misc.h"
#include "main.h"
#include "commands.h"

int main(int argc, char *argv[]) {
  char ** args = prompt();

  isCommand(args);

  pid_t p = fork();
  if(p<0){
    perror("forkfail");
    exit(1);
  } else if (p==0){
    //CHILD
    //execvp here
  } else if (p>0){
    //PARENT
    //wait until child dies then prompt again (i have NO idea how this'll work)
  }

  /*
  i dunno where to put this
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

//checks if args is cd/exit/anything that isn't a program, and executes it.
int isCommand(char ** args){
  if (strcmp(args[0], "cd") == 0){
    cd(args);
  } else if (strcmp(args[0], "exit")){
    exit(1);
  }
}
