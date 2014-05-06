#include <stdio.h> 
#include <fcntl.h>
#include <stdlib.h>

main() {
	int fifo_server,fifo_client;
	char *buf;
	char *msg = "andrea";

	fifo_server=open("fifo_server",O_WRONLY);//open fifo server
	if(fifo_server < 0) {
		printf("Error in opening file");
		exit(-1);
	}
	write(fifo_server,msg,100*sizeof(char));//writes msg in fifo server
	printf("msg written in fifo_server: %s\n",msg);

	fifo_client=open("fifo_client",O_RDONLY);//open fifo client
	if(fifo_client < 0) {
		printf("Error in opening file");
	  exit(-1);
	}

	buf=malloc(100*sizeof(char));
	read(fifo_client,buf,100*sizeof(char));
	printf("\n ***Reply from server is: %s***\n",buf);

	//close(fifo_server);
	//close(fifo_client);
}