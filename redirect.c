#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "parse.h"
#include "main.h"

/******** TO DO: error handling !!!!!!!!!! *********/
// can use printErr() since main.h is included
// check execvp work

void redirect(char* line){
    char* args[32];

    // parse line into args array
    parse_args(line,args); 

    // establish files
    char* input_file = NULL;
    char* output_file = NULL;

    for (int i = 0; args[i]!=NULL;i++){
        // finding <
        if (strcmp(args[i],"<")==0){
            if(args[i+1]!=NULL){
                input_file = args[i+1]; // the file to take from is found after <
                args[i]=NULL; // remove redirection operator from the array
            }
        }
        if (strcmp(args[i],">")==0){
            // finding >
            if(args[i+1]!=NULL){
                output_file = args[i+1]; // the file to redirect to is found after >
                args[i]=NULL; // remove redirection operator from the array
            }
        }
    }

    pid_t p = fork();

    if (p == 0){ // child process in fork
        // this means that it looks like this: a < _.txt
        // redirect stuff from the file taken from (in read_input) to run into program a
        if (input_file != NULL){
            int read_input = open(input_file, O_RDONLY, 0);
            if (read_input==-1) printErr();
            // args[0] would be the program
            dup2(args[0], read_input);
        }

        // this means that it looks like this: b  > _.txt
        // redirect stuff from program b output (read_output) into file
        if (output_file != NULL){
            int read_output = open(output_file,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (read_output==-1) printErr();
            // args[1] would be the file
            dup2(args[1], read_output);
        }
    }

    execvp(args[0], args); // error handling? perror? 
    // not right, make sure execvp happens after 

/*
advice from class lessons...
    int fd1 = open("foo.txt", O_WRONLY);
    int FILENO = stdout;
    int backup_stdout = dup( FILENO ) // save stdout for later
    dup2(fd1, FILENO) //sets FILENO's entry to the file for fd1.
    printf("TO THE FILE!!!\n");
    fflush(stdout);//not needed when a child process exits, becaue exiting a process will flush automatically.
    dup2(backup_stdout, FILENO) //sets FILENO's entry to backup_stdout, which is stdout

Your shell project will need to use dup() and dup2()
It should be reasonably straight forward that you can implement the redirection operators < or > by changing the 
input to be a file instead of stdin, or the output to be a file not stdout.
*/
}