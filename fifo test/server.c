#include <stdio.h> 
#include <fcntl.h>
#include <stdlib.h>

/*main() 
{
	FILE *file1;
	int fifo_server,fifo_client;
	int choice;
	char *buf;

	fifo_server = open("fifo_server",O_RDWR);
	if(fifo_server<1) {
	 printf("Error opening file");
	}
	read(fifo_server,&choice,sizeof(int));
	sleep(1);//wait for the server answer for thet time

	fifo_client = open("fifo_client",O_RDWR);
	if(fifo_server<1) {
	 printf("Error opening file");
	}

	switch(choice) {
	case 1: 
	 buf="Linux";
	 write(fifo_client,buf,10*sizeof(char)); 
	 printf("\n Data sent to client \n");
	 break;
	case 2:
	 buf="debian";
	 write(fifo_client,buf,10*sizeof(char)); 
	 printf("\nData sent to client\n");
	 break;
	case 3: 
	 buf="2.6.32";
	 write(fifo_client,buf,10*sizeof(char)); 
	 printf("\nData sent to client\n");
	}

	close(fifo_server);
	close(fifo_client);
}*/

main() {
	FILE *file1;
	int fifo_server,fifo_client;
	char *msg;
	char *buf;

	fifo_server = open("fifo_server",O_RDWR);//open fifo server
	if(fifo_server<1) {
	 printf("Error opening file");
	}
	buf = malloc(100*sizeof(char));//allocate buffer for read
	read(fifo_server,buf,100*sizeof(char));//read from fifo server and puts the result in buf
	printf("msg read in fifo_server\n");
	printf("***data read: %s***\n", buf);
	sleep(1);

	fifo_client = open("fifo_client",O_RDWR);//open fifo client
	if(fifo_server<1) {
	 printf("Error opening file");
	}

	buf = "test";
	write(fifo_client,buf,100*sizeof(char)); 
	printf("\n Data sent to client \n");

	close(fifo_server);
	close(fifo_client);
}