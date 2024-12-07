#include "parse.h"
#include "main.h"
#include "redirect.h"

int err(){
  printf("Error %d: %s\n", errno, strerror(errno));
  //exit(1);
}

int main(int argc, char *argv[]) {
    while (1) {
        int i = 0;
        char ** commands = prompt();
        while (commands[i]) {
            char ** args = (char**)calloc(16, sizeof(char*));
            parse_args(commands[i], args);
            for (int i = 0; i < 16; i++) {
                args[i] = strsep(&args[i], "\n");
            }

            if (strcmp(args[0], "cd") == 0) {cd(args);}
            else if (strcmp(args[0], "exit") == 0) {exit(0);}
            else {
                int j = 0;
                int is_piped = 0; //check if pipe haandeld
                int is_redirected = 0; //check if rediericoted

                while (args[j]!=NULL){
                    if(strcmp(args[j],"|")==0){
                        piping(args);
                        is_piped = 1;
                        break;
                    }
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


void piping(char** args){
    char* args1[150];
    char* args2[150];

    // separate into args1
    int i = 0;
    while(args[i]!=NULL && strcmp(args[i],"|")!=0){
        args1[i] = args[i];
        i++;
    }
    args1[i] = NULL;
    i++; // ignore pipe

    // separate into args2
    int j = 0;
    while(args[i]!=NULL){
        args2[j] = args[i];
        i++;
        j++;
    }
    args2[j] = NULL;



    pid_t p1 = fork();
    if (p1 == 0){ // child
        //heres my temp file where all stduot will go
        int temp_f = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(temp_f==-1)err();

        //redirect stdout into temp_
        dup2(temp_f, STDOUT_FILENO);
        close(temp_f);

        execvp(args1[0], args1);
        perror("wuhoh");
        exit(1);

    }
    if (p1>0){
        waitpid(p1,NULL,0); // waits for child to finish
    }

    pid_t p2 = fork();
    if (p2 == 0){ // child2
        //opening temp again so i can read it
        int temp_f = open("temp.txt", O_RDONLY,0);
        if(temp_f==-1)err();

        dup2(temp_f, STDIN_FILENO);
        close(temp_f);

        execvp(args2[0], args2);
        perror("lalala");
        exit(1);

    }
    if (p2>0){
        waitpid(p2,NULL,0); // waits for child to finish
    }

    remove("temp.txt"); // looked this up
}

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

// prints char **
void printchars(char ** arr){
  printf("[");
  while(*arr!=NULL){
    printf("%s ", *arr);
    arr++;
  }
  printf("]\n");
}


// not done at all, need to fix. figure out directing to files?


// change. pipe should take in array of separated args

/*
Implement simple pipes. Only one pipe at a time is required.
The pipe operator | redirects one program's output to be another program's input. e.g. ls | wc would run ls and use the output from ls as the input for wc.
Check out popen() for the advanced way of doing this, otherwise use a temp file.

run c1 and redirect stdout to a temp file!!!!
run c2 and redirect the temp file to stdin!!!
remove the temp file when done!!!

*/
// Redirect stdout from one program to stdin of the next.
/*sorry commenting out for now bc its giving me errors
void pipe(char* command1, char* command2){
    char* args1[32];
    char* args2[32];
    // copies command into args arrays, separates arguments
    parse_args(command1, args1);
    parse_args(command1, args2);

    // create temporary file for first command's output
    int temp = open("first_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(temp==-1) err();

    pid_t p1 = fork();
    if (p1 == 0){ // child
        // write output to file, then direct this output into the second arugment... ok so try and use the redirect command from redirect.c...
        // does this make sense?
        // should redirect the output into arg2 (after the pipe), then execute thaat
        //redirect("first_output.txt > %s", args2);
    }
}
*/
