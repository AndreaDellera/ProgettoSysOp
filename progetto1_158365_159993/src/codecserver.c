/*
Andrea Dellera 158365
Gianluca Bortoli 159993
 
Progetto 1
Anno accademico 2013/2014
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "functions.h"

int main(int argc, char **argv) {    
    //##### Gestione input da linea di comando #############################
    char *server_name = NULL;
    char *minvalue = NULL;
    char *maxvalue = NULL;
    char *maxtext = NULL;
    int k;
    
    char *options = "n:t:m:M:"; // i ":" indicano che il parametro ha un argomento
    opterr = 0;
    
    while ((k = getopt (argc, argv, options)) != -1) {
        switch (k) {
            case 'n'://nome server
                server_name = optarg;
                break;
                
            case 't'://max text
                maxtext = optarg;
                break;
                
            case 'm'://min key
                minvalue = optarg;
                break;
                
            case 'M'://max key
                maxvalue = optarg;
                break;
                
            case '?'://caso in cui non riconosco nessuno dei caratteri
                printf("qualcosa non va\n");
            default:
                abort ();
        }
    }
    
    //##### Creazione dello storico dei server creati, con relativi parametri, nel file lista_server.txt ######
    //senza l'attributo -n non va creato nessuno server
    
    FILE *fp;
    fp = fopen("lista_server.txt", "a+");
    char* toWrite = "";
    if(server_name != NULL){
        strcat(toWrite, server_name);
        strcat(toWrite, " ");
        
        if(maxtext != NULL){
            strcat(toWrite, maxtext);
            strcat(toWrite, " ");
        } else {
            strcat(toWrite, "? ");//il carattere ? serve per denotare un parametro non presente in inpu, per poi poter leggere la lista dei server con i relativi parametri in modo corretto
        }

        if(minvalue != NULL){
            strcat(toWrite, minvalue);
            strcat(toWrite, " ");
        } else {
            strcat(toWrite, "? ");
        }

        if(maxvalue != NULL){
            strcat(toWrite, maxvalue);
            strcat(toWrite, " ");
        } else {
            strcat(toWrite, "? ");
        }
        
        fprintf(fp, "%s\n", toWrite);
    }
    
    //TODO: apertura fifo server
    //create_fifo(server_name);

    return 0;
}