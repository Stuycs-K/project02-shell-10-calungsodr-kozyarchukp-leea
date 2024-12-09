#include "parse.h"
#include "main.h"
#include "redirect.h"

/******** TO DO: error handling !!!!!!!!!! *********/
// can use printErr() since main.h is included
// check execvp work

//takes int ind and char** args, removes index ind from args
void removeArg(char** args, int ind){
    for (int i = ind; args[i]!=NULL; i++){
        args[i]=args[i+1];
    }
}

//executes redirect, given stdin
void redirect(char** args){

    // establish files
    char* input_file = NULL;
    char* output_file = NULL;
    int backup_stdin = dup(STDIN_FILENO);
    int backup_stdout = dup(STDOUT_FILENO);

    for (int i = 0; args[i]!=NULL;i++){
        // finding <
        if (strcmp(args[i],"<")==0){
            if(args[i+1]!=NULL){
                input_file = args[i+1]; // the file to take from is found after <
                removeArg(args,i); // remove <
                removeArg(args,i); // remove file name
                i--; // go back after removing!
            }
        }
        if (strcmp(args[i],">")==0){
            // finding >
            if(args[i+1]!=NULL){
                output_file = args[i+1]; // the file to redirect to is found after >
                removeArg(args,i); // remove <
                removeArg(args,i); // remove file name
                i--; // go back after removing!
            }
        }
    }

    pid_t p = fork();

    if (p == 0){ // child process in fork

      //  fflush(stdout);

        // DOES NOT WORK YET
        // this means that it looks like this: a < _.txt
        // redirect stuff from the file taken from (in read_input) to run into program a
        if (input_file != NULL){
            int read_input = open(input_file, O_RDONLY, 0);
            if (read_input==-1) err();
          //  backup_stdin = dup(STDIN_FILENO);
            dup2(read_input, STDIN_FILENO);
            close(read_input);

        }

        // this means that it looks like this: b  > _.txt
        // redirect stuff from program b output into file
        if (output_file != NULL){
            int redirect_to_output = open(output_file,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (redirect_to_output==-1) err();

          //  backup_stdout = dup(STDOUT_FILENO);
          //  fflush(stdout);
            dup2(redirect_to_output, STDOUT_FILENO);
            close(redirect_to_output);
        }

        execvp(args[0], args);
        perror("execvp failed!");
    }
    if (p>0){ // parent process should wait until child finishes! i think!
        int status;
        waitpid(p, &status, 0);

        close(backup_stdin);
        close(backup_stdout);

    }
}
