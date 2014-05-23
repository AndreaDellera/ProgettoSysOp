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
#include <unistd.h>
#include "functions.h"


int main(int argc, char **argv) {    
    //##### Gestione input da linea di comando #############################
    char *server_name = malloc(256*sizeof(char));
    char *key = NULL;
    int file = 0;
    char *msg = NULL;
    char *action = malloc(sizeof(char)*2);//il carattere \0 va considerato; per quello *2
    char *output = malloc(256*sizeof(char));
    strcpy(output, "do_nothing");
    int show_all_messages_flag = 0;
    int index = -1;
    int k;
    FILE *pf;
 
    char *options = "n:k:f:m:edo:si:";
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
                //si suppone che il file di testo da cui leggere il messaggio in input venga creato
                //appositamente all'interno della cartella /bin che viene generata dopo ogni compilazione
                file = 1;

                char *nome_file = malloc(256*sizeof(char));
                nome_file = optarg;
                pf = fopen(nome_file, "r");
                if(pf == NULL){
                    printf("file di input non trovato\n");
                    exit(1);
                }
                
                msg = malloc(100000*sizeof(char));
                fscanf(pf, "%s", msg);
                fclose(pf);
                break;
                
            case 'm'://messaggio
                msg = optarg;
                break;

            case 'e'://encode
                sprintf(action,"%c",'0');
                break;

            case 'd'://decode
                sprintf(action,"%c",'1');
                break;
                
            case 'o'://file output dove scrivere il messaggio una volta de/criptato
                output = optarg;
                break;
            
            case 's'://show all messages stored in the server (ONLY chrypted ones!)
                show_all_messages_flag = 1;
                break;
            
            case 'i': //decode the i-esimo message
                index = atoi(optarg);
                sprintf(action,"%c",'1');
                break;
                
            case '?'://caso in cui non riconosco nessuno dei caratteri
                printf("Parameter not foundn");

            default:
                abort();
        }
    }

    /*COMPONGO NOME CLIENT*/
    char *client_name = malloc(sizeof(char)*32);
    sprintf(client_name,"client%d",getpid());

    //i-esimo messaggio
    if(index != -1){
        msg = read_encoded_msg(server_name, index);
    }
    
    if(show_all_messages_flag){
        show_all_messages(server_name);
    }else{
        /*AVVIO CLIENT CON I PARAMETRI DATI*/
        run_client(server_name, client_name, key, file, msg, action, output);
        unlink(client_name);
    }
    free(action);
    free(client_name);
    return 0;
}