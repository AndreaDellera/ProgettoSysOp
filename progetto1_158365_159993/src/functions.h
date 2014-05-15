/*
Andrea Dellera 158365
Gianluca Bortoli 159993
 
Progetto 1
Anno accademico 2013/2014
*/

#ifndef _functions_h
#define _functions_h

/*
 - fifo_server è la fifo dove il client scrive ed il server legge
 - fifo_client è dove il server scrive ed il client legge
*/
void cript(char* msg, char* key); //funzione per criptare il messaggio
void decript(char* msg, char* key); //funzione per decriptare il messaggio

int create_fifo(char* name); //funzione per creare una fifo con un determinato nome

void run_client(char* server_name, char* client_name, char* key, int file, char* msg, int action, char* output);
void run_server(char* server_name);

#endif
