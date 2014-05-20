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
#include "functions.h"

const int NUMB = 26;

typedef int bool; //per usare bool
#define true 1
#define false 0

void cript(char* msg, char* key){
    int k = 0;//puntatore alla chiave
    int m = 0;//puntatore al messaggio
    int lKey = 0;
    while(key[k] != '\0'){
        if (key[k] >= 65 && key[k] <= 90){
            key[k] += ('a' - 'A');
        }
        k++;
    }
    lKey = k;
    
    k = 0;
    bool maiusc = false;//così quando scrivo il messaggio criptato rispetta le maiuscole/minuscole del messaggio originale
    
    while(msg[m] != '\0'){
        if (msg[m] >= 65 && msg[m] <= 90){
            msg[m] += ('a' - 'A');
            maiusc = true;
        } else {
            maiusc = false;
        }
        
        int off = ((int)msg[m] + (int)key[k] - 96*2 -1) % NUMB;//offset da sommare al carattere --> xk devo togliere da tutto una 'a', mentre un'altra 'a' è lo psostamento di +1 e perciò devo togliere 96 e non 97
        
        if((msg[m]>= 'a' && msg[m]<='z')||(msg[m]>= 'A' && msg[m]<='Z')){//gestisco gli spazi del messaggio iniziale che vanno rispettati e anche i casatteri speciali
            if(maiusc){//gestisco se è maiuscola la lettera del messaggio iniziale
                msg[m] = 'A' + off;
            }else{
                msg[m] = 'a' + off;
            }
            k = (k + 1) % lKey;
        }
        m++;
    }
}

void decript(char* msg, char* key){
    int k = 0;//puntatore alla chiave
    int m = 0;//puntatore al messaggio
    int lKey = 0;
    while(key[k] != '\0'){
        if (key[k] >= 65 && key[k] <= 90){
            key[k] += ('a' - 'A');
        }
        k++;
    }
    lKey = k;
    
    k = 0;
    bool maiusc = false;//così quando scrivo il messaggio criptato rispetta le maiuscole/minuscole del messaggio originale
    
    while(msg[m] != '\0'){
        if (msg[m] >= 65 && msg[m] <= 90){
            msg[m] += ('a' - 'A');
            maiusc = true;
        } else {
            maiusc = false;
        }
        
        int off = ((int)msg[m] - (int)key[k] -1) % NUMB;//offset che mi dice la distanza tra due lettere misurata sottraendo i rispettici caratteri ASCII
        
        if((msg[m]>= 'a' && msg[m]<='z')||(msg[m]>= 'A' && msg[m]<='Z')){//gestisco gli spazi del messaggio iniziale che vanno rispettati e anche i casatteri speciali
            if(maiusc){//gestisco se è maiuscola la lettera del messaggio iniziale
                msg[m] = 'A' + off;
                if((int)msg[m] < 65){//se la lettera scende sotto 65 vuol dire che devo ripartire dalla z
                    msg[m] += NUMB;
                }
            }else{
                msg[m] = 'a' + off;
                if((int)msg[m] < 97){
                    msg[m] += NUMB;
                }
            }
            k = (k + 1) % lKey;
        }
        m++;
    }
}

int create_fifo(char* name){
    return mkfifo(name, 0666); //0666 dà permessi in lettura e scrittura alla fifo a tutti gli utenti
}

void run_client(char* server_name, char* client_name, char* key, int file, char* msg, char *action, char* output){
    int fifo_server;// va dal client al server
    int fifo_client;// va dal server al client
    char *buf;
    int file_cl;//file per fifo client

    int maxtext, minvalue, maxvalue;

    /*CREO LA FIFO DEL CLIENT*/
    file_cl = create_fifo(client_name);
    if(file_cl < 0){
        printf("impossibile creare fifo per il client %s\n", client_name);
        exit(-1);
    }

    /*CONTROLLO DEI PARAMETRI DEL SERVER (min e max chiave e lunghezza massima testo)*/
    FILE *pf;
    char *tmp_server_name = NULL;
    char *tmp = NULL;
    pf = fopen("lista_server.txt", "r");
    if (pf == NULL){
        printf("lista server vuota\n");
        exit(1);
    }

    printf("11111\n");

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
    }
    
    if (pf == NULL){
        printf("server non presente\n");
        exit(1);
    }

    printf("22222\n");

    /*COMUNICAZIONE TRA SERVER E CLIENT*/
    fifo_server = open(server_name, O_WRONLY);//open fifo server in r/w
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

    fifo_client = open(client_name, O_RDONLY);//apre fifo client e si mette in ascolto per una risposta da parte del server
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

void run_server(char* server_name, int maxtext, int minvalue, int maxvalue){
    int fifo_server, fifo_client;
    char *nvalue = NULL;
    char *buf = NULL;
    char *key = NULL;
    char *msg = NULL;
    char *client_name = NULL;
    int action;
    /*
    int minvalue = -1;
    int maxvalue = -1;
    int maxtext = -1;
    */

    /*CONTROLLO DEI PARAMETRI DEL SERVER DAL FILE CON IL LOG DEI SERVER CREATI*/
    FILE *pf;
    char * tmp_server_name = NULL;
    char *tmp = NULL;
    pf = fopen("lista_server.txt", "r");
    if (pf == NULL){
        printf("lista server vuota\n");
        exit(1);
    }

    /*while(feof(pf) == 0){
        fscanf(pf, "%s", tmp_server_name);
        if(strcmp(server_name, tmp_server_name) == 0){ //stringhe uguali
            fscanf(pf, "%s", tmp);
            if(strcmp(tmp, "?") != 0){
                maxtext = atoi(tmp);
                printf("::%d\n",maxtext);
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
    }
    
    if (pf == NULL){
        printf("server non presente\n");
        exit(1);
    }
    */
    
    /*COMUNICAZIONE TRA SERVER E CLIENT*/
    fifo_server = open(server_name, O_RDONLY);//apre fifo server in read per ricevere i parametri dal client
    if(fifo_server < 1){
        printf("Errore apertura fifo_server");
        exit(1);
    }

    //legge dalla fifo_server il nome del client
    buf = malloc(32*sizeof(char));
    read(fifo_server,buf,strlen(msg));
    client_name = buf;

    char *terminatore= malloc(4*sizeof(char)); //dopo i parametri invio sempre '****'
    read(fifo_server, terminatore, 4*sizeof(char));
    if(strcmp(terminatore, "****") > 0){//controllo del terminatore per vedere che non ci siano messaggi/chiavi più lunghe del massimo consentito
        printf("messaggio troppo lungo\n");
        exit(1);
    }

    /*CONTROLLI DA ESEGUIRE SUI PARAMENTRI*/
    msg = malloc(maxtext * sizeof(char));
    read(fifo_server, msg, maxtext * sizeof(char));//lettura messaggio

    read(fifo_server, terminatore, 4*sizeof(char));
    if(strcmp(terminatore, "****") > 0){
        printf("messaggio troppo lungo\n");
        exit(1);
    }
    
    //lettura chiave
    key = malloc(maxvalue * sizeof(char));
    read(fifo_server, key, maxvalue * sizeof(char));
    if(strlen(key) < minvalue){
        printf("lunghezza chiave troppo piccola\n");
        exit(1);
    }
    read(fifo_server, terminatore, 4*sizeof(char));
    if(strcmp(terminatore, "****") > 0){
        printf("chiave troppo lunga");
        exit(1);
    }

    //lettura azione da fare (de/codifica)
    char *action_buff = NULL;
    read(fifo_server, action_buff, sizeof(char));
    action = atoi(action_buff);
    
    read(fifo_server, terminatore, 4*sizeof(char));
    if(strcmp(terminatore, "****") > 0){
        printf("chiave troppo lunga");
        exit(1);
    }
    
    printf("msg read in fifo_server\n");
    
    //viene eseguita la de/codifica del messaggio
    if(action == 0){
        cript(msg, key);
    }
    if(action == 1){
        decript(msg, key);
    }
    
    //scrittura le messaggio de/criptato al client per rispondergli
    fifo_client = open(client_name, O_WRONLY);
    if(fifo_client < 1) {
        printf("Errore apertura fifo_client");
        exit(2);
    }
    
    //invia il messaggio al client
    write(fifo_client, msg, maxtext);
    printf("\n Data sent back to client \n");

    /*CHIUSURA CANALE DI COMUNICAZIONE*/
    close(fifo_server);
    close(fifo_client);
}
