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

void redirect(char** args){

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

            int stdin = STDIN_FILENO; 
            int backup_stdin = dup(stdin);
            dup2(stdin, read_input);
            execvp(args[0], args);
            fflush(stdin);
            dup2(backup_stdin, stdin);
            
        }

        // this means that it looks like this: b  > _.txt
        // redirect stuff from program b output into file
        if (output_file != NULL){
            int redirect_to_output = open(output_file,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (redirect_to_output==-1) printErr();

            int stdout = STDOUT_FILENO; 
            int backup_stdout = dup(stdout);
            dup2(redirect_to_output, stdout);
            execvp(args[0], args);
            fflush(stdout);
            dup2(backup_stdout, stdout);
        }
    }


/*
advice from class lessons...
    int fd1 = open("foo.txt", O_WRONLY);
    int stdout = STDOUT_FILENO;//stdout filenumber is 1, but this makes it clear
    int backup_stdout = dup( stdout ) // save for later
    dup2(fd1, stdout); //sets stdout's entry to the file "foo.txt".
    printf("TO THE FILE!!!\n");
    fflush(stdout);//not needed when a child process exits, becaue exiting a process will flush automatically.
    dup2(backup_stdout, stdout); //sets the stdout entry to backup_stdout, which is the original stdout
Your shell project will need to use dup() and dup2()
It should be reasonably straight forward that you can implement the redirection operators < or > by changing the 
input to be a file instead of stdin, or the output to be a file not stdout.
*/
}