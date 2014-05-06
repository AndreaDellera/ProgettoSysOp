/*
Andrea Dellera 158365
Gianluca Bortoli 159993
 
Progetto 1
Anno accademico 2013/2014
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "functions.h"

int main(int argc, char **argv) {    
  //##### Gestione input da linea di comando #############################
  char *client_name = NULL;
  char *key = NULL;
  char *msg = NULL;
  char *e = NULL;//-encode 
  char *d = NULL;//-decode
  char *o = NULL;

  int index;
  int k;
     
  char *options = "n:k:m:M:"; // i ":" indicano che il parametro ha un argomento
      
  opterr = 0;
       
  while ((k = getopt (argc, argv, options)) != -1) {
    switch (k) {
    case 'n'://nome client
      client_name = optarg;
      break;

    case 'k'://chiave
      maxtext = optarg;
      break;
                
    case 'm'://file origine messaggio
      msg = optarg;
      break;
            
    case '?'://caso in cui non riconosco nessuno dei caratteri
      if (isprint (optopt))
        fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        return 1;
    default:
      abort ();
    }
  }

  printf ("client_name = %s, key = %s, msg = %s\n", client_name, key, msg); 
  
  return 0;
}