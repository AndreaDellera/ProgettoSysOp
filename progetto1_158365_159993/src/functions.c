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
#include <unistd.h>
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
    /*SCRIVO I MESSAGGI CODIFICATI IN UN FILE PER STORARLI*/

    
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
    char *buf = NULL;
    int file_cl;//file per fifo client

    int maxtext, minvalue, maxvalue;

    /*CONTROLLO DEI PARAMETRI DEL SERVER (min e max chiave e lunghezza massima testo)*/
    FILE *pf;
    char *tmp_server_name = NULL;
    char *tmp = NULL;
    pf = fopen("lista_server.txt", "r");
    if (pf == NULL){
        printf("Empty server list\n");
        exit(1);
    }

    while(feof(pf) == 0){
        tmp_server_name = malloc(256 * sizeof(char));
        fscanf(pf, "%s", tmp_server_name);
        if(strcmp(server_name, tmp_server_name) == 0){ //stringhe uguali
            tmp = malloc(256 * sizeof(char));
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
    
    free(tmp_server_name);
    free(tmp);
    
    if (pf == NULL){
        printf("Server not present\n");
        exit(1);
    }
    fclose(pf);

    /*Controllo la validità dei parametri prima di scrivere ognuno nella fifo*/
    if(strlen(msg) > maxtext){
        printf("Message too long\n");
        write(fifo_server,"parametri_invalidi",256*sizeof(char));
        exit(-1);
    }

    if(strlen(key) > maxvalue || strlen(key) < minvalue){
        printf("Incorrect key length\n");
        write(fifo_server,"parametri_invalidi",256*sizeof(char));
        exit(-1);
    }

    /*COMUNICAZIONE TRA SERVER E CLIENT*/
    fifo_server = open(server_name, O_WRONLY);//open fifo server in r/w
    if(fifo_server < 0) {
        printf("Error in opening file\n");
        exit(-1);
    }

    /*CREO LA FIFO DEL CLIENT*/
    file_cl = create_fifo(client_name);
    if(file_cl < 0){
        printf("Unable to create a fifo for %s\n", client_name);
        exit(-1);
    }

    write(fifo_server, client_name, 256*sizeof(char));//scrive il nome della fifo dove il server andrà a scrivere
    write(fifo_server, msg, maxtext * sizeof(char));//writes msg in fifo server      
    write(fifo_server, key, maxvalue * sizeof(char));    
    write(fifo_server, action, sizeof(char));    

    printf("***End write from client to server***\n");

    fifo_client = open(client_name, O_RDONLY);//apre fifo client e si mette in ascolto per una risposta da parte del server
    if(fifo_client < 0) {
        printf("Error in opening file");
        exit(-1);
    }

    read(fifo_client, msg, maxtext);

    FILE *out;
    if(strcmp(output,"do_nothing") != 0){
        out = fopen(output, "a+");
        fprintf(out, "%s\n", msg);
    }else{
        printf("***Reply from server is: %s***\n", msg);
    }
    fclose(out);

    /*CHIUSURA CANALE DI COMUNICAZIONE*/
    //chiude le fifo
    if((close(fifo_server)) == -1)
        printf("fifo server not closed\n");
    
    if((close(fifo_client)) == -1)
        printf("fifo client not closed\n");

    if((unlink(client_name)) == -1)
        printf("fifo client not deleted\n");//elimina fifo client
}

void run_server(char* client_name, char* server_name, int maxtext, int minvalue, int maxvalue, int index){
    int fifo_server, fifo_client;
    char *nvalue = NULL;
    char *buf = NULL;
    char *key = NULL;
    char *msg = NULL;
    int action;
    
    /*COMUNICAZIONE TRA SERVER E CLIENT*/
    fifo_server = open(server_name, O_RDONLY);//apre fifo server in read per ricevere i parametri dal client
    if(fifo_server < 1){
        printf("Error in opening fifo server\n");
        unlink(server_name);
        exit(1);
    }

    /*CONTROLLI DA ESEGUIRE SUI PARAMENTRI*/
    msg = malloc(maxtext * sizeof(char));
    read(fifo_server, msg, maxtext * sizeof(char));//lettura messaggio
    
    //lettura chiave
    key = malloc(maxvalue * sizeof(char));
    read(fifo_server, key, maxvalue * sizeof(char));

    //lettura azione da fare (de/codifica)
    char *action_buff = malloc(2*sizeof(char));
    read(fifo_server, action_buff, sizeof(char));
    action = atoi(action_buff);
    free(action_buff);
    
    printf("***Msg read in fifo_server***\n");
    
    //viene eseguita la de/codifica del messaggio
    if(action == 0){
        printf("messaggio da codificare: %s\n", msg);
        cript(msg, key);
        write_encoded_msg(server_name, msg);
        printf("\tmessage encoded!\n");
    }
    if(action == 1){
        decript(msg, key);
    }
    
    //scrittura le messaggio de/criptato al client per rispondergli
    fifo_client = open(client_name, O_WRONLY);
    if(fifo_client < 1) {
        printf("Error in opening fifo client\n");
        exit(2);
    }
    
    //invia il messaggio al client
    write(fifo_client, msg, maxtext);
    printf("***Data sent back to client***\n");

    /*CHIUSURA CANALE DI COMUNICAZIONE*/
    if((close(fifo_server)) == -1)
        printf("fifo server not closed\n");
    
    if((close(fifo_client)) == -1)
        printf("fifo client not closed\n");
}

void write_encoded_msg(char* server_name, char* msg){
    FILE *pf;
    char* name = malloc(256*sizeof(char));
    strcpy(name, server_name);
    strcat(name, "_history.txt");
    printf("\t\tnome file %s\n", name);
    pf = fopen(name, "a+");
    if(pf == NULL){
        printf("File not found\n");
        exit(1);
    }
    fprintf(pf, "%s\n", msg);
    free(name);
    fclose(pf);
}

//funzione che decodifica un certo messaggio
char* read_encoded_msg(char* server_name, int index){
    FILE *pf;
    char* name = malloc(256*sizeof(char));
    strcpy(name, server_name);
    strcat(name, "_history.txt");
    pf = fopen(name, "r");
    if(pf == NULL){
        printf("History file not found\n");
        exit(1);
    }
    int i = 0;
    char *m = malloc(100000*sizeof(char));
    while(i < index && !feof(pf)){
        fscanf(pf, "%s", m);
    }
    fscanf(pf, "%s", m);
    free(name);
    fclose(pf);
    return m;
}

//funzione che mostra tutti i messaggi codificati da un certo server
void show_all_messages(char* server_name){
    int i = 0;
    FILE *pf;
    char* name = malloc(256*sizeof(char));
    strcpy(name, server_name);
    strcat(name, "_history.txt");
    printf("nome composto: %s\n", name);
    pf = fopen(name, "r");
    if(pf == NULL){
        printf("File not found\n");
        exit(1);
    }
    char *m = malloc(100000*sizeof(char));
    while(!feof(pf)){
        fscanf(pf, "%s", m);
        printf("%d: %s\n",i++, m);
    }
    free(name);
    fclose(pf);
}