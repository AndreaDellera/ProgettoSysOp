/*
 Andrea Dellera 158365
 Gianluca Bortoli 159993
 
 Progetto 1
 Anno accademico 2013/2014
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    char* line = NULL;
    char fine[] ="-1";
    int len;

    
    char *nvalue = NULL;
    int minvalue = -1;
    int maxvalue = -1;
    int index;
    int k;
    
    char *options ="Qn:m:M:"; // i : indicano che il parametro ha un argomento
    
    opterr = 0;
    for (;;) {
        printf("> ");

        getline(&line, (size_t*)&len, stdin);
    
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        if (strcmp(line, "quit") == 0)
            break;
        printf("%s\n",strcat("./",line));
    //system(fine);
  } 
  
  fflush(stdout);
  free(line);

  return 0;
}
