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
    char *server_name = NULL;
    char *key = NULL;
    int file = 0;
    char *msg = NULL;
    char *action = malloc(sizeof(char)*2);//il carattere \0 va considerato; per quello *2
    char *output = NULL;
    
    int k;
    
    char *options = "n:k:fm:edo:";
    opterr = 0;
    
    while ((k = getopt (argc, argv, options)) != -1) {
        switch (k) {
            case 'n'://nome server a cui connettersi
                server_name = optarg;
                break;
                
            case 'k'://chiave
                key = optarg;
                break;
                
            case 'f'://flag per prendere il messaggio da un file
                file = 1;//TODO: file da input
                break;
                
            case 'm'://messaggio
                msg = optarg;
                break;

            case 'e':
                sprintf(action,"%c",'0');
                break;

            case 'd':
                sprintf(action,"%c",'1');
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

    char *commandClient = malloc(sizeof(char)*2048);
    char *commandServer = malloc(sizeof(char)*2048);

    /*COMPONGO COMANDO PER IL CLIENT*/
    char *client_name = malloc(sizeof(char)*32);
    sprintf(client_name,"client%d",getpid());
    
    printf("client name = %s\n", client_name);
    printf("azione: %s\n", action);

    if(server_name != NULL) {
        strcat(commandClient, "client -s ");
        strcat(commandClient, server_name);

        if(key != NULL){
            strcat(commandClient, " -k ");
            strcat(commandClient, key);
        }

        if(client_name != NULL){
            strcat(commandClient, " -n ");
            strcat(commandClient, client_name);
        }

        if(action[0] == '0'){
            strcat(commandClient, " -e");
        } else if (action[0] == '1') {
            strcat(commandClient, " -d");
        }  
    }


    printf("comando client: %s\n\n", commandClient);

    /*COMPONGO COMANDO PER IL SERVER*/    
    sprintf(commandServer,"server -n %s",server_name);
    printf("comando server: %s\n", commandServer);
    
    /*AVVIO CLIENT E SERVER CON I PARAMETRI DATI*/
    //system(client_cmd);
    //system(server_cmd);

    return 0;
}