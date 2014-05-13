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
#include <unistd.h>
#include "functions.h"


int main(int argc, char **argv) {    
    //##### Gestione input da linea di comando #############################
    char server_name[100000] = "";
    char key[100000] = "";
    int file = 0;
    char msg[100000] = "";
    int action = -1;
    char output[100000] = "";
    
    int k;
    
    char *options = "n:k:fm:edo:";
    opterr = 0;
    
    while ((k = getopt (argc, argv, options)) != -1) {
        switch (k) {
            case 'n'://nome server a cui connettersi
                strcat(server_name, optarg);
                break;
                
            case 'k'://chiave
                strcat(key, optarg);
                break;
                
            case 'f'://flag per prendere il messaggio da un file
                file = 1;
                break;
                
            case 'm'://file origine messaggio
                strcat(msg, optarg);
                break;
                
            case 'e'://flag encode
                action = 0;
                break;
                
            case 'd'://flag decode
                action = 1;
                break;
                
            case 'o'://file output dove scrivere il messaggio una volta de/criptato
                strcat(output, optarg);
                break;
                
            case '?'://caso in cui non riconosco nessuno dei caratteri
                printf("c'è qualcosa che non va\n");
            default:
                abort ();
        }
    }

    /*COMPONGO COMANDO PER IL CLIENT*/
    char numb[] = "";
    sprintf(numb, "%d", getpid());
    char client_name[100000] = "client";
    strcat(client_name,numb);
    
    printf("client name = %s\n", client_name);

    char pippo[] = "";
    char toWrite[] = "";
    if(strcmp(server_name,"") != 0) {
        printf("ss: %s\n\n", server_name);
        strcat(toWrite, "client -s ");
        strcat(toWrite, server_name);
        strcat(pippo, "server -s ");
        strcat(pippo, server_name);

        if(strcmp(key,"") != 0){
            strcat(toWrite, " -k ");
            strcat(toWrite, key);
        }

        if(strcmp(client_name,"") != 0){
            strcat(toWrite, " -n ");
            strcat(toWrite, client_name);
        }

        if(action == 0){
            strcat(toWrite, " -e");
        } else {
            strcat(toWrite, " -d");
        }      
    }
    printf("aa: %s\n\n", toWrite);

    /*COMPONGO COMANDO PER IL SERVER*/
    //printf("comando client: %s\n\n", toWrite);

    strcat(pippo,"server -n ");
    strcat(pippo, server_name);

    printf("comando server: %s\n", pippo);
    printf("comando client: %s\n\n", toWrite);
  
    
    /*AVVIO CLIENT E SERVER CON I PARAMETRI DATI*/
    //system(client_cmd);
    //system(server_cmd);

    return 0;
}