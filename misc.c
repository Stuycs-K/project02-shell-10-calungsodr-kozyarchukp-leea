#include "misc.h"
#include "main.h"

//prints char **
void printchars(char ** arr){
  printf("[");
  while(*arr!=NULL){
    printf("%s ", *arr);
    arr++;
  }
  printf("]\n");
}

//checks if two strings are equals. returns 1 if they are, 0 if they aren't.
int equals(char * s1, char * s2){
  if (strcmp(s1, s2) == 0){
    return 1;
  } else return 0;
}
