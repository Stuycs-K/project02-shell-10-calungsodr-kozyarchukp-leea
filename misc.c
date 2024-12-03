#include "misc.h"
#include "main.h"

// prints char **
void printchars(char ** arr){
  printf("[");
  while(*arr!=NULL){
    printf("%s ", *arr);
    arr++;
  }
  printf("]\n");
}
