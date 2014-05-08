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
#include "function.h"

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
    
    server s;
	int fifo_server, fifo_client;
    char *key = NULL;
    char *text = NULL;
    char* server_name = NULL;
    char* client_name = NULL;
    int azione;
    char *buf;
    
    char *nvalue = NULL;
    int minvalue = -1;
    int maxvalue = -1;
    int maxtext = -1;
    int index;
    int k;
    
    char *options ="n:"; // i ":" indicano che il parametro ha un argomento
    
    opterr = 0;
    
    while ((k = getopt (argc, argv, options)) != -1) {
        switch (k)
        {
            case 'n'://nome
                server_name = optarg;
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
    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    
    /*CONTROLLO DEI PARAMETRI DEL SERVER*/
    
    FILE *fp;
    char * tmp_server_name = NULL;
    char *tmp = NULL;
    fp = fopen("lista_server.txt", "r");
    if (pf == NULL){
        printf("lista server vuota\n")
        exit(1);
    }
    while(!foef(fp)){
        fscanf(pf, "%s", tmp_server_name);
        if(strcmq(server_name, tmp_server_name) == 0){ //stringhe uguali
            fscanf(pf, "%s", tmp);
            if(strcmq(tmp, "?") != 0){
                maxtext = atoi(tmp);
            }else{
                maxtext = 100000;
            }
            fscanf(pf, "%s", tmp);
            
            if(strcmq(tmp, "?") != 0){
                minvalue = atoi(tmp);
            }
            else{
                minvalue = 100000;
            }
            fscanf(pf, "%s", tmp);
            
            if(strcmq(tmp, "?") != 0){
                maxvalue = atoi(tmp);
            }
            else{
                maxvalue = 100000;
            }
        }else{
            for(int i = 0; i < 3; i++)
                fscanf(pf, "%s", tmp_server_name);
        }
    }
    
    if (pf == NULL){
        printf("server non presente\n")
        exit(1);
    }
    
    /*----------------------------------*/
    
	fifo_server = open(server_name,O_RDONLY);//apre fifo server in read
	if(fifo_server < 1){
        printf("Errore apertura fifo_server");
        return(1);
	}

    /*LETTURA NOME DELLA FIFO CLIENT*/
    buf = malloc(256*sizeof(char));//alloca il buffer
    read(fifo_server,buf,strlen(msg));//legge dalla fifo_server e scrive il messaggio in buf
    client_name = buf;
    /*----------------------------------*/

    /*CONTROLLI DA ESEGUIRE SUI PARAMENTRI*/
    char *terminatore= malloc(4*sizeof(char)); // dopo i parametri invio sempre '****' che
    //lettura messaggio
    msg = malloc(maxtext * sizeof(char));
    read(client_name, msg, maxtext * sizeof(char));

    //controllo del terminatore per vedere che non ci siano messaggi/chiavi più lunghe del massimo consentito
    read(server_name, terminatore, 4*sizeof(char));
    if(strcmp(terminatore, "****") > 0){
        printf("messaggio troppo lungo\n");
        return(1);
    }
    
    //lettura chiave
    key = malloc(maxvalue * sizeof(char));
    read(server_name, key, maxvalue * sizeof(char));
    if(strlen(key) < minvalue){
        printf("lunghezza chiave troppo piccola\n");
        return(1);
    }
    read(server_name, terminatore, 4*sizeof(char));
    if(strcmp(terminatore, "****") > 0){
        printf("chiave troppo lunga");
        return(1);
    }
        //lettura azione da fare de/codifica
    int action_buff = NULL;
    read(server_name, action_buff, sizeof(char));
    
    read(server_name, terminatore, 4*sizeof(char));
    if(strcmp(terminatore, "****") > 0){
        printf("chiave troppo lunga");
        return(1);
    }
    

    
    /*----------------------------------*/

    
	printf("msg read in fifo_server\n");
    
    //viene eseguita la de/codifica del messaggio
    if(azione == '0'){
        cript(msg, key);
    }
    if(azione == '1'){
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
    
	close(fifo_server);
	close(fifo_client);
    
    return 0;
}
