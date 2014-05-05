#include <stdio.h> 
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	int file1,file2;

	file1 = mkfifo("fifo_server", 0666);
	if(file1 < 0) {
	 printf("Unable to create a fifo server");
	 exit(-1);
	}

	
	
	printf("fifos server and child created successfuly\n");
    return 0;
}