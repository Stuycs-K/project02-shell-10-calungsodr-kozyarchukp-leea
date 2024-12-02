#include "parse.h"
int main(int argc, char *argv[]) {
    char * args[16];
    printf("prompt ");
    char line_buff[256];
    fgets(line_buff, 255, stdin);
    parse_args(line_buff, args); 
    execvp(args[0], args);
}