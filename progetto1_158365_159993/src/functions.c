/*
Andrea Dellera 158365
Gianluca Bortoli 159993
 
Progetto 1
Anno accademico 2013/2014
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
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
    return file = mkfifo(name, 0666); //0666 dà permessi in lettura e scrittura alla fifo a tutti gli utenti
}


