#include "parse.h"
#include "misc.h"
#include "main.h"
#include "redirect.h"

int err(){
  printf("Error %d: %s\n", errno, strerror(errno));
  exit(1);
}

int main(int argc, char *argv[]) {
    while (1) {
        char ** args = prompt();
        pid_t p = fork();
        if(p < 0) {
            perror("forkfail");
            err();
        } else if (p == 0){
            //CHILD
            execvp(args[0], args);
        } else {
            //PARENT - wait until child is done
            int status;
            wait(&status);
        }
    }
}


//prints cwd path and parses user input. returns array of args from stdin
char ** prompt(){
  char ** args = (char**)calloc(16, sizeof(char*));
  char buffer[256];
  getcwd(buffer, 256);
  printf("%s$ ", buffer);
  fflush(stdout);
  //i think fflush is supposed to go here maybe idk.........
  char * line_buff = (char*)calloc(256, sizeof(char));
  fgets(line_buff, 255, stdin);
  parse_args(line_buff, args);
  return args;
}

// not done at all, need to fix. figure out directing to files?
/*
Implement simple pipes. Only one pipe at a time is required.
The pipe operator | redirects one program's output to be another program's input. e.g. ls | wc would run ls and use the output from ls as the input for wc.
Check out popen() for the advanced way of doing this, otherwise use a temp file.

run c1 and redirect stdout to a temp file!!!!
run c2 and redirect the temp file to stdin!!!
remove the temp file when done!!!

*/
<<<<<<< HEAD
void piper(char* command1, char* command2){
=======

// Redirect stdout from one program to stdin of the next.
void pipe(char* command1, char* command2){
>>>>>>> raechel
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