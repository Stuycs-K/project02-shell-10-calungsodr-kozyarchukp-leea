#include "parse.h"

int printErr(){
  printf("Error %d: %s\n", errno, strerror(errno));
  return -1;
}

int main(int argc, char *argv[]) {
    char * args[16];
    char buffer[256];
    getcwd(buffer, 256);
    printf("%s", buffer);
    char line_buff[256];
    fgets(line_buff, 255, stdin);
    parse_args(line_buff, args); 
    execvp(args[0], args);
    fflush(stdout);
}

/*
Implement simple pipes. Only one pipe at a time is required.
The pipe operator | redirects one program's output to be another program's input. e.g. ls | wc would run ls and use the output from ls as the input for wc.
Check out popen() for the advanced way of doing this, otherwise use a temp file.
*/
void pipe(char* command1, char* command2){
    char* args1[32];
    char* args2[32];
    // copies command into args arrays, separates arguments
    parse_args(command1, args1);
    parse_args(command1, args2);

    // create temporary file for first command's output
    int temp = open("first_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(temp==-1) printErr();

    pid_t p1 = fork();
    if (p1 == 0){ // child
        // use the < or > code to write to a file...??? unsure how for now
        // will figure this out
    }
}