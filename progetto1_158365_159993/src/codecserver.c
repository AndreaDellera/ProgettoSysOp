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
#include <unistd.h>
#include "functions.h"

int main(int argc, char **argv) {    
    //##### Gestione input da linea di comando #############################
    char *server_name = NULL;
    char *minvalue = NULL;
    char *maxvalue = NULL;
    char *maxtext = NULL;
    int k;
    int file;//file per fifo server
    
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
    //##### Senza l'attributo -n non va creato nessuno server!!    
    FILE *fp;
    fp = fopen("lista_server.txt", "a+");
    if(server_name != NULL){
        fprintf(fp,"%s ",server_name);

        if(maxtext != NULL){
            fprintf(fp,"%s ",maxtext);
        } else {
            fprintf(fp,"?");
            /*
            il carattere ? serve per denotare un parametro non presente in input 
            per poi poter leggere la lista dei server con i relativi parametri in modo corretto
            */
        }

        if(minvalue != NULL){
            fprintf(fp, "%s ", minvalue);
        } else {
            fprintf(fp,"? ");
        }

        if(maxvalue != NULL){
            fprintf(fp, "%s ",maxvalue);
        } else {
            fprintf(fp,"? ");
        }
        
        fprintf(fp, "\n");
    }
    fclose(fp);

    /*CREO LA FIFO DEL SERVER E AVVIO SERVER CON I PARAMETRI DATI*/
    file = create_fifo(server_name); //creo una fifo con il nome passato con argomento -n
    if(file < 0) {//error handling
        printf("impossibile creare una fifo per il server %s\n", server_name);
        exit(-1);
    }

    while(1){
        int fifo_server = open(server_name, O_RDONLY);//apre fifo server in read per ricevere i parametri dal client
        if(fifo_server < 1){
            printf("Errore apertura fifo_server\n");
            unlink(server_name);
            exit(1);
        }
        //legge dalla fifo_server il nome del client
        char *client_name = malloc(256*sizeof(char));
        read(fifo_server, client_name, 256*sizeof(char));
        
        if(client_name != NULL){
            printf("client: %s\n", client_name);
            run_server(client_name, server_name, atoi(maxtext), atoi(minvalue), atoi(maxvalue));
            read(fifo_server, client_name, 256*sizeof(char));
        }
        free(client_name);
        close(fifo_server);
    }
    
    unlink(server_name);

    return 0;
}