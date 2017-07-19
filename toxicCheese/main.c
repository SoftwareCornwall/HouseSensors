#include <stdlib.h>
#include <fcntl.h> // for open and flags
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h> //for ioctl
#include <time.h>
#include <stdio.h>

#define READ 0x5F

char * filename = "/dev/i2c-1";

void readBytes(int fd, char buffer[], void* offset){
	write(fd, offset, 1);
	size_t bytesToRead = 1;
	size_t bytesRead = read(fd, buffer, bytesToRead);
	if(bytesRead != bytesToRead){
		printf("error reading from: %s\n", filename);
		close(fd);
		exit(1);
	}
}
int main(int argc, char *argv[]){
	char *outputFile = "~/.humidity";
	char buffer[20];
	int fd = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0){
		printf("could not open: %s\n", filename);
		exit(1);	
	}

	if(ioctl(fd, I2C_SLAVE, READ)){
		printf("error setting up i2c port\n");
		exit(1);	
	}

	while(1){

		//buffer[0] = 0x28;
		int x = 0;

		printf("humidity: %d, %d %d\n", buffer[0], buffer[1], buffer[2]);
		sleep(3);
		if(x == 10)
			break;
		x++;
	}
	close(fd);
	return 0;
}
