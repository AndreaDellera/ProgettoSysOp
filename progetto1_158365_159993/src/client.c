/*
Andrea Dellera 158365
Gianluca Bortoli 159993
 
Progetto 1
Anno accademico 2013/2014
*/

/*DEPRECATED*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "functions.h"


int main(int argc, char** argv) {//DEPRECATED!!!! Questa roba diventa una funzione che viene chiamata da codecserver, che prende in input i dati e mi 
                                //risparmio un altro parsing inutile e una chiamata a system
    /*
     Il client usa, per fare il suo lavoro
     - fifo in entrata, ergo fifo_client
     - fifo in uscita, ergo fifo_server
     - messaggio da criptare
     - chiave
    */
    int fifo_server;// va dal client al server
    int fifo_client;// va dal server al client
	char *buf;
    
    /*GESTIONE INPUT DA LINEA DI COMANDO*/
    char *client_name = NULL;
    char *server_name = NULL;
    char *key = NULL;
    int file = 0;
    char *msg = NULL;
    char* action = NULL;
    char *output = NULL;
    
    int maxtext, minvalue, maxvalue;
    
    int k;
    
    char *options = "n:k:fm:edo:";
    opterr = 0;
    
    while ((k = getopt (argc, argv, options)) != -1) {
        switch (k) {
            case 's'://nome server
                server_name = optarg;
                break;
                
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
                action = "0";
                break;
                
            case 'd'://flag decode
                action = "1";
                break;
                
            case 'o'://file output dove scrivere il messaggio una volta de/criptato
                output = optarg;
                break;
                
            case '?'://caso in cui non riconosco nessuno dei caratteri
                printf("qualcosa non va\n");
                exit(1);
            default:
                abort ();
        }
    }
    
    /*CONTROLLO DEI PARAMETRI DEL SERVER (min e max chiave e lunghezza massima testo)*/
    FILE *pf;
    char * tmp_server_name = NULL;
    char *tmp = NULL;
    pf = fopen("lista_server.txt", "r");
    if (pf == NULL){
        printf("lista server vuota\n");
        exit(1);
    }

    while(feof(pf) == 0){
        fscanf(pf, "%s", tmp_server_name);
        if(strcmp(server_name, tmp_server_name) == 0){ //stringhe uguali
            fscanf(pf, "%s", tmp);
            if(strcmp(tmp, "?") != 0){
                maxtext = atoi(tmp);
            }else{
                maxtext = 100000;
            }
            fscanf(pf, "%s", tmp);
            
            if(strcmp(tmp, "?") != 0){
                minvalue = atoi(tmp);
            }
            else{
                minvalue = 100000;
            }
            fscanf(pf, "%s", tmp);
            
            if(strcmp(tmp, "?") != 0){
                maxvalue = atoi(tmp);
            }
            else{
                maxvalue = 100000;
            }
        }else{
            int i;
            for(i = 0; i < 3; i++)
                fscanf(pf, "%s", tmp_server_name);
        }
        
        k = getopt (argc, argv, options);
    }
    
    if (pf == NULL){
        printf("server non presente\n");
        exit(1);
    }

    /*COMUNICAZIONE TRA SERVER E CLIENT*/
	fifo_server = open(server_name,O_WRONLY);//open fifo server in r/w
	if(fifo_server < 0) {
		printf("Error in opening file");
		exit(-1);
	}
    
    write(fifo_server, client_name, 256*sizeof(char));//scrive il nome della fifo dove il server andrà a scrivere
    write(fifo_server, "****", 4 * sizeof(char));
	write(fifo_server, msg, maxtext);//writes msg in fifo server
    write(fifo_server, "****", 4 * sizeof(char));//carattere separatore
    write(fifo_server, key, maxvalue);
    write(fifo_server, "****", 4 * sizeof(char));
    write(fifo_server, action, sizeof(char));
    write(fifo_server, "****", 4 * sizeof(char));

	fifo_client = open(client_name,O_RDONLY);//apre fifo client e si mette in ascolto per una risposta da parte del server
	if(fifo_client < 0) {
		printf("Error in opening file");
	    exit(-1);
	}

	buf = malloc(maxtext * sizeof(char));
	read(fifo_client, buf, maxtext);
    msg = buf;
	printf("\n ***Reply from server is: %s***\n",msg);

    /*CHIUSURA CANALE DI COMUNICAZIONE*/
	close(fifo_server);//chiude le fifo
	close(fifo_client);
    unlink(client_name);//elimina fifo client
}