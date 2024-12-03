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

    // read commands from input file to stdin
    pid_t p = fork();

    if (p == 0){ // child process in fork
        if (input_file != NULL){
            int read_input = open(input_file, O_RDONLY, 0);
            if (read_input==-1) printErr();
            dup2(read_input, stdin); // read input file to stdin ???
        }

        // write stdout to new output file
        if (output_file != NULL){
            int read_output = open(output_file,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (read_output==-1) printErr();
            dup2(read_output, stdout); // stdout goes to output file ???
        }
    }

    execvp(args[0], args); // error handling? perror?

}