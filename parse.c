#include "parse.h"
#include "main.h"
//takes string line, puts all the pieces into argary separated by spaces
void parse_args( char * line, char ** arg_ary ) {
    char *curr = line;
    int i = 0;
    while (curr) {
        arg_ary[i] = strsep(&curr, " ");
        i++;
    }
    arg_ary[i] = NULL;
}
