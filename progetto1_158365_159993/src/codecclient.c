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
    char *server_name = NULL;
    char *key = NULL;
    int file = 0;
    char *msg = NULL;
    char *action = NULL;
    char *output = NULL;
    
    int k;
    
    char *options = "n:k:fm:edo:";
    opterr = 0;
    
    while ((k = getopt (argc, argv, options)) != -1) {
        switch (k) {
            case 'n'://nome client
                server_name = optarg;
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
                action = "0";
                break;
                
            case 'd'://flag decode
                action = "1";
                break;
                
            case 'o'://file output dove scrivere il messaggio una volta de/criptato
                output = optarg;
                break;
                
            case '?'://caso in cui non riconosco nessuno dei caratteri
                printf("c'è qualcosa che non va\n");
            default:
                abort ();
        }
    }
    
    /*COMPONGO COMANDO PER IL CLIENT*/
    char* client_name = "client1"; //TODO: implementare generazione nomi diversi per ogni client che si crea
    char* client_cmd = "client -s ";
    if((server_name != NULL) && (action != NULL) && (key != NULL)){
        strcat(client_cmd, server_name);
        strcat(client_cmd, " -n ");
        strcat(client_cmd, client_name);
        strcat(client_cmd, " -k ");
        strcat(client_cmd, key);
        if(strcmp(action, "0") == 0){
            strcat(client_cmd, " -e");//eseguo crypt
        }
        if(strcmp(action, "1") == 0){
            strcat(client_cmd, " -d");//eseguo decrypt
        }
    }
    
    /*COMPONGO COMANDO PER IL SERVER*/
    char* server_cmd = "server -n ";
    strcat(server_cmd, server_name);
    
    system(client_cmd);
    system(server_cmd);

    return 0;
}