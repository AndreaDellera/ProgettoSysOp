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
    char *server_name;
    char *key;
    int file = 0;
    char *msg;
    char *action;
    char *output;
    
    int k;
    
    char *options = "n:k:fm:a:o:";
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
                file = 1;
                break;
                
            case 'm'://file origine messaggio
                msg = optarg;
                break;
                
            case 'a'://flag de/code --> 0 encode // 1 decode
                if(atoi(optarg)==0){
                    action = "0";
                } else if(atoi(optarg)==1){
                    action = "1";
                }
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

    char commandClient[] = "";
    char commandServer[] = "";

    /*COMPONGO COMANDO PER IL CLIENT*/
    char numb[] = "";
    sprintf(numb, "%d", getpid());
    char client_name[100000] = "client";//il client_name è "client<pid>"
    strcat(client_name, numb);
    
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

        if(action == "0"){
            strcat(commandClient, " -e");
        } else if (action == "1") {
            strcat(commandClient, " -d");
        }  
    }

    printf("comando client: %s\n\n", commandClient);

    /*COMPONGO COMANDO PER IL SERVER*/
    //strcat(commandServer,"server -n ");
    //strcat(commandServer, server_name);

    //printf("comando server: %s\n", commandServer);
    
  
    
    /*AVVIO CLIENT E SERVER CON I PARAMETRI DATI*/
    //system(client_cmd);
    //system(server_cmd);

    return 0;
}