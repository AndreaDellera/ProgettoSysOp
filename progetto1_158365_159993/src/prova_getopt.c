/*
 Andrea Dellera 158365
 Gianluca Bortoli 159993
 
 Progetto 1
 Anno accademico 2013/2014
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main (int argc, char **argv) {
  char *nvalue = NULL;
  int minvalue = -1;
  int maxvalue = -1;
  int index;
  int k;
  
  char *options ="n:m:M:"; // i : indicano che il parametro ha un argomento
  
  opterr = 0;
    
  while ((k = getopt (argc, argv, options)) != -1)
    switch (k)
		{
    case 'n':
      nvalue = optarg;
      break;
            
    case 'm':
      minvalue = atoi(optarg);
      break;
        
    case 'M':
      maxvalue = atoi(optarg);
      break;
        
    case '?':
      if (optopt == 'n')
        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint (optopt))
        fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        return 1;
     default:
       abort ();
    }
    
  printf ("nvalue = %s, minvalue = %d, maxvalue = %d\n", nvalue, minvalue, maxvalue);
    
  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  return 0;
}