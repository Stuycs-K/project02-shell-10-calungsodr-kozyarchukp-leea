#include "parse.h"
#include "main.h"
#include "redirect.h"
#include "pipe.h"

//prints errno
void err(){
  printf("Error %d: %s\n", errno, strerror(errno));
  //exit(1);
}

//prints terminal, parses, calls pipes and redirect when necessary
int main(int argc, char *argv[]) {
    while (1) {
        int i = 0;
        char ** commands = prompt();
        while (commands[i]) {
            char ** args = (char**)calloc(16, sizeof(char*));
            parse_args(commands[i], args);
            int a = 0;
            while (args[a]) {
                a++;
            }
            args[a-1] = strsep(&args[a-1], "\n");

            if (strcmp(args[0], "cd") == 0) {cd(args);}
            else if (strcmp(args[0], "exit") == 0) {exit(0);}
            else {
                int j = 0;
                int is_piped = 0; //check if pipe haandeld
                int is_redirected = 0; //check if rediericoted

                while (args[j]){
                    if(strcmp(args[j],"|")==0){
                        piping(args);
                        is_piped = 1;
                        break;
                    }
                    else j++;
                }
                j = 0;
                while (is_piped == 0 && args[j]) {
                    if(strcmp(args[j],"<")==0 || strcmp(args[j],">")==0){
                        redirect(args);
                        is_redirected = 1;
                    }
                    else j++;
                }
                if (!is_piped && !is_redirected){
                  pid_t p = fork();
                  if (p < 0) {
                      perror("forkfail");
                      err();
                  } else if (p == 0){ //CHILD
                      execvp(args[0], args);
                  } else { //PARENT - wait until child is done
                      int status;
                      wait(&status);
                  }
                }
            }
            i++;
        }
    }
}


//prints cwd path and parses user input. returns array of commands from stdin
char ** prompt(){
  char buffer[256];
  getcwd(buffer, 256);
  printf("%s$ ", buffer);
  fflush(stdout);
  char * line_buff = (char*)calloc(256, sizeof(char));
  char * val = fgets(line_buff, 255, stdin);
  if (val == NULL) {
    printf("\n");
    exit(0);
  }
  char *curr = line_buff;
  int i = 0;
  char ** commands = (char**)calloc(16, sizeof(char*));
  while (curr) {
    commands[i] = strsep(&curr, ";");
    i++;
  }
  return commands;
}

//executes cd given char ** args which is stdin
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