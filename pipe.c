#include "main.h"
#include "pipe.h"
#include "redirect.h"

//executes a pipe given char** args which is stdin
void piping(char** args){
    char* args1[150];
    char* args2[150];

    // separate into args1
    int i = 0;
    while(strcmp(args[i],"|")!=0){
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

    // a < c.txt | b > d.txt
    if (args1[1] && strcmp(args1[1], "<") == 0 && args2[1] && strcmp(args2[1], ">") == 0) {
        int backup_stdin = dup(STDIN_FILENO);
        if (!args1[2]) err();
        char* input_file = args1[2];
        int backup_stdout = dup(STDOUT_FILENO);
        if (!args2[2]) err();
        char* output_file = args2[2];
        removeArg(args1, 1);
        removeArg(args1, 1);
        removeArg(args2, 1);
        removeArg(args2, 1);
        pid_t p1 = fork();
        if (p1 == 0){ // child
            int read_input = open(input_file, O_RDONLY, 0);
            if (read_input==-1) err();
            
            dup2(read_input, STDIN_FILENO);
            close(read_input);
            
            //heres my temp file where all stduot will go
            int temp_f = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(temp_f==-1)err();

            //redirect stdout into temp_
            dup2(temp_f, STDOUT_FILENO);
            close(temp_f);
            close(read_input);

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

            int redirect_to_output = open(output_file,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (redirect_to_output==-1) err();
            dup2(redirect_to_output, STDOUT_FILENO);
            close(redirect_to_output);

            execvp(args2[0], args2);
            perror("lalala");
            exit(1);

        }
        if (p2>0){
            waitpid(p2,NULL,0); // waits for child to finish
        }

        remove("temp.txt"); // looked this up
        close(backup_stdin);
        close(backup_stdout);
    }
    // ONLY prog < file | prog2
    else if (args1[1] && strcmp(args1[1], "<") == 0) {
        int backup_stdin = dup(STDIN_FILENO);
        if (!args1[2]) err();
        char* input_file = args1[2];
        removeArg(args1, 1);
        removeArg(args1, 1);
        pid_t p1 = fork();
        if (p1 == 0){ // child
            int read_input = open(input_file, O_RDONLY, 0);
            if (read_input==-1) err();
            
            dup2(read_input, STDIN_FILENO);
            close(read_input);
            
            //heres my temp file where all stduot will go
            int temp_f = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(temp_f==-1)err();

            //redirect stdout into temp_
            dup2(temp_f, STDOUT_FILENO);
            close(temp_f);
            close(read_input);

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
        close(backup_stdin);
    }
    //ONLY prog | prog > file
    else if (args2[1] && strcmp(args2[1], ">") == 0) {
        int backup_stdout = dup(STDOUT_FILENO);
        if (!args2[2]) err();
        char* output_file = args2[2];
        removeArg(args2, 1);
        removeArg(args2, 1);
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

            int redirect_to_output = open(output_file,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (redirect_to_output==-1) err();
            dup2(redirect_to_output, STDOUT_FILENO);
            close(redirect_to_output);

            execvp(args2[0], args2);
            perror("lalala");
            exit(1);

        }
        if (p2>0){
            waitpid(p2,NULL,0); // waits for child to finish
        }

        remove("temp.txt"); // looked this up
        close(backup_stdout);
    }

    else {
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
}