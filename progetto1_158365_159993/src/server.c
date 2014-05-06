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
     
     ./server server_name fifo_client
     
     il messaggio, la chiave e l'azione da svolgere sono letti dalla fifo, separati l'uno dall'altro da un carattere '-'
     
     azione = 0 -> codifica
     azione = 1 -> decodifica
     */
    server s;
	int fifo_server,fifo_client;
    char *key;
    char* fifo_server_name;
    char* fifo_client_name;
    int azione;
    char *buf;
    
    /*
     TODO: lettura argv
     */
    if(argc < 2){
        printf("Numero argomenti insufficiente\n");
    }else{
        s = (server)argv[0];
        fifo_client_name = argv[1];
    }

    //apre fifo server in read/write
	fifo_server = open(s.fifo_server_name,O_RDWR);
	if(fifo_server < 1){
        printf("Errore apertura fifo_server");
        return(1);
	}
    
    
    /* TODO: implementare la lettura dalla fifo
	buf = malloc(256*sizeof(char));//alloca il buffer
	read(fifo_server,buf,strlen(msg));//legge dalla fifo_server e scrive il messaggio in buf
    */
    
    
    
	printf("msg read in fifo_server\n");
	printf("***data read: %s***\n", buf);
    
    //viene eseguita la de/codifica del messaggio
    if(azione){
        decript(msg, key);
    }
    if(!azione){
        cript(msg, key);
    }
    
    //scrittura le messaggio de/criptato al client
	fifo_client = open(fifo_client_name,O_RDWR);
	if(fifo_server < 1) {
	 printf("Errore apertura fifo_client");
        return(2);
	}
    
    //invia il messaggio al client
	write(fifo_client,buf,strlen(msg));
    
	printf("\n Data sent to client \n");

	close(fifo_server);
	close(fifo_client);
    
    return 0;
}
