#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * The strdup funtion returns a pointer to a new string which is the duplicate of the string s 
 *
 *
 * */



int main()
{
    char *s;

  s = strdup("Shawty");

  if (s == NULL){
    fprintf(stderr,"Cannot Allocate Enough mem with malloc\n");
    return (EXIT_FAILURE);
  }

  printf("%p\n", (void*)s);

  return (EXIT_SUCCESS);
}

