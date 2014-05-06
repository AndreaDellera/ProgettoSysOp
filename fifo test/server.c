#include <stdio.h> 
#include <fcntl.h>
#include <stdlib.h>

main() {
	int fifo_server,fifo_client;
	char *buf;

	while(1) {
		fifo_server = open("fifo_server",O_RDONLY);//open fifo server
		if(fifo_server<1) {
		 printf("Error opening file");
		}
		buf = malloc(100*sizeof(char));//allocate buffer for read
		read(fifo_server,buf,100*sizeof(char));//read from fifo server and puts the result in buf
		printf("msg read in fifo_server\n");
		printf("***data read: %s***\n", buf);
		sleep(1);

		fifo_client = open("fifo_client",O_WRONLY);//open fifo client
		if(fifo_server<1) {
		 printf("Error opening file");
		}

		buf = "test";
		write(fifo_client,buf,100*sizeof(char)); 
		printf("\n Data sent to client \n");
	}

	//close(fifo_server);
	//close(fifo_client);
}