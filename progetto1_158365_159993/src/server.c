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
    /*
    Il server usa, per fare il suo lavoro:
    - fifo in entrata, fifo_server
    - fifo in uscita, fifo_client
    - messaggio da criptare
    - chiave
     
    Diciamo che gli argomenti vengono presi così
     
    ./server -n server_name
     
    il messaggio, la chiave e l'azione da svolgere sono letti dalla fifo, separati l'uno dall'altro da un carattere '-'
     
    azione = 0 -> codifica
    azione = 1 -> decodifica
     */
    int fifo_server, fifo_client;
    char *key = NULL;
    char *msg = NULL;
    char* server_name = NULL;
    char* client_name = NULL;
    int action;
    char *buf;
    
    char *nvalue = NULL;
    int minvalue = -1;
    int maxvalue = -1;
    int maxtext = -1;
    int index;
    int k;
    int optind;
    
    char *options ="n:"; // i ":" indicano che il parametro ha un argomento
    
    int opterr = 0;
    k = getopt (argc, argv, options);
    while (k != -1) {
        switch (k)
        {
            case 'n'://nome
                server_name = optarg;
                break;
                
            case '?'://caso in cui non riconosco nessuno dei caratteri
                printf("qualcosa non va\n");
                exit(1);
            default:
                abort();
        }
    }
    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    
    /*CONTROLLO DEI PARAMETRI DEL SERVER*/
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
	fifo_server = open(server_name,O_RDONLY);//apre fifo server in read per ricevere i parametri dal client
	if(fifo_server < 1){
        printf("Errore apertura fifo_server");
        return(1);
	}

    //legge dalla fifo_server il nome del client
    buf = malloc(256*sizeof(char));
    read(fifo_server,buf,strlen(msg));
    client_name = buf;

    /*CONTROLLI DA ESEGUIRE SUI PARAMENTRI*/
    char *terminatore= malloc(4*sizeof(char)); //dopo i parametri invio sempre '****' che
    msg = malloc(maxtext * sizeof(char));
    read(fifo_server, msg, maxtext * sizeof(char));//lettura messaggio

    read(fifo_server, terminatore, 4*sizeof(char));
    if(strcmp(terminatore, "****") > 0){//controllo del terminatore per vedere che non ci siano messaggi/chiavi più lunghe del massimo consentito
        printf("messaggio troppo lungo\n");
        return(1);
    }
    
    //lettura chiave
    key = malloc(maxvalue * sizeof(char));
    read(fifo_server, key, maxvalue * sizeof(char));
    if(strlen(key) < minvalue){
        printf("lunghezza chiave troppo piccola\n");
        return(1);
    }
    read(fifo_server, terminatore, 4*sizeof(char));
    if(strcmp(terminatore, "****") > 0){
        printf("chiave troppo lunga");
        return(1);
    }

    //lettura azione da fare (de/codifica)
    char *action_buff = NULL;
    read(fifo_server, action_buff, sizeof(char));
    action = atoi(action_buff);
    
    read(fifo_server, terminatore, 4*sizeof(char));
    if(strcmp(terminatore, "****") > 0){
        printf("chiave troppo lunga");
        return(1);
    }
    
	printf("msg read in fifo_server\n");
    
    //viene eseguita la de/codifica del messaggio
    if(action == 0){
        cript(msg, key);
    }
    if(action == 1){
        decript(msg, key);
    }
    
    //scrittura le messaggio de/criptato al client
	fifo_client = open(client_name, O_WRONLY);
	if(fifo_client < 1) {
        printf("Errore apertura fifo_client");
        return(2);
	}
    
    //invia il messaggio al client
	write(fifo_client, msg, maxtext);
	printf("\n Data sent to client \n");

    /*CHIUSURA CANALE DI COMUNICAZIONE*/
	close(fifo_server);
	close(fifo_client);
    
    return 0;
}
