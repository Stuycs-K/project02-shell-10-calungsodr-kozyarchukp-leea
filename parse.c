#include "parse.h"
#include "main.h"
//takes string line, puts all the space-separated pieces into argary
void parse_args( char * line, char ** arg_ary ) {
    char *curr = line;
    int i = 0;
    while (curr) {
        arg_ary[i] = strsep(&curr, " ");
        i++;
    }
    arg_ary[i] = NULL;
}
