/*
Andrea Dellera 158365
Gianluca Bortoli 159993
 
Progetto 1
Anno accademico 2013/2014
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

main() {
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
    char action = NULL;
    char *output = NULL;
    
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
                action = '0';
                break;
                
            case 'd'://flag decode
                action = '1';
                break;
                
            case 'o'://file output dove scrivere il messaggio una volta de/criptato
                output = optarg;
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
    /*----------------------------------------*/
    
    /*CONTROLLO DEI PARAMETRI DEL SERVER*/
    int minvalue = -1;
    int maxvalue = -1;
    int maxtext = -1;
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
                maxtext = 100000; //lunghezza massima di default, se non specificata dall'utente
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
/*------*/

	fifo_server = open(server_name,O_RDWR);//open fifo server
	if(fifo_server < 0) {
		printf("Error in opening file");
		exit(-1);
	}
    
	write(fifo_server, msg, maxtext);//writes msg in fifo server
    write(fifo_server, "****", 4 * sizeof(char));
    write(fifo_server, key, maxvalue);
    write(fifo_server, "****", 4 * sizeof(char));
    write(fifo_server, action, sizeof(char));
    write(fifo_server, "****", 4 * sizeof(char));


	fifo_client = open("fifo_client",O_RDWR);//open fifo client
	if(fifo_client < 0) {
		printf("Error in opening file");
	  exit(-1);
	}

	buf = malloc(100*sizeof(char));
	read(fifo_client, msg, strlen(msg));
	printf("\n ***Reply from server is: %s***\n",buf);

	close(fifo_server);
	close(fifo_client);
    unlink(fifo_client);
}