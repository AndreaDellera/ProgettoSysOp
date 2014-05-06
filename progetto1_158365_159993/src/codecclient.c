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
  int file = 0;
  char *msg = NULL;
  int encode = 0;
  int decode = 0;
  char *output = NULL;

  int k;
     
  char *options = "n:k:fm:edo:";
  opterr = 0;
       
  while ((k = getopt (argc, argv, options)) != -1) {
    switch (k) {
    case 'n'://nome client
      client_name = optarg;
      break;

    case 'k'://chiave
      key = optarg;
      break;

    case 'f'://flag per prendere il messaggio da un file
      file = 1;
      break;
                
    case 'm'://file origine messaggio
      msg = optarg;
      break;

    case 'e'://flag encode
      encode = 1;
      break; 

    case 'd'://flag decode
      decode = 1;
      break;

    case 'o'://file output dove scrivere il messaggio una volta de/criptato
      output = optarg;
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

  return 0;
}