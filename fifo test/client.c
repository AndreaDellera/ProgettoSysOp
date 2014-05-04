#include <stdio.h> 
#include <fcntl.h>
#include <stdlib.h>

main() {
	FILE *file1;
	int fifo_server,fifo_client;
	char str[256];
	char *buf;
	char *msg = "messaggio";

	fifo_server=open("fifo_server",O_RDWR);//open fifo server
	if(fifo_server < 0) {
		printf("Error in opening file");
		exit(-1);
	}
	write(fifo_server,msg,100*sizeof(char));//writes msg in fifo server
	printf("msg written in fifo_server: %s\n",msg);

	fifo_client=open("fifo_client",O_RDWR);//open fifo client
	if(fifo_client < 0) {
		printf("Error in opening file");
	  exit(-1);
	}

	buf=malloc(100*sizeof(char));
	read(fifo_client,buf,100*sizeof(char));
	printf("\n ***Reply from server is: %s***\n",buf);

	close(fifo_server);
	close(fifo_client);
}

/*main()
{
	FILE *file1;
	int fifo_server,fifo_client;
	char str[256];
	char *buf;
	int choice=1;
	printf("Choose the request to be sent to server from options below");
	printf("\n\t\t Enter 1 for O.S.Name \n \
	               Enter 2 for Distribution \n \
	               Enter 3 for Kernel version \n");
	scanf("%d",&choice);

	fifo_server=open("fifo_server",O_RDWR);
	if(fifo_server < 0) {
		printf("Error in opening file");
		exit(-1);
	}

	write(fifo_server,&choice,sizeof(int));

	fifo_client=open("fifo_client",O_RDWR);
	if(fifo_client < 0) {
		printf("Error in opening file");
	  exit(-1);
	}

	buf=malloc(10*sizeof(char));
	read(fifo_client,buf,10*sizeof(char));
	printf("\n ***Reply from server is %s***\n",buf);

	close(fifo_server);//closes both the fifos
	close(fifo_client);
}*/