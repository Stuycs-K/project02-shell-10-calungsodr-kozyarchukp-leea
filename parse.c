#include "parse.h"
#include "main.h"

// takes string line, separates the string by spaces and places into array of strings. returns the separated array.
void parse_args( char * line, char ** arg_ary ) {
    char *curr = line;
    int i = 0;
    while (curr) {
        arg_ary[i] = strsep(&curr, " ");
        i++;
    }
    arg_ary[i] = NULL;
}
