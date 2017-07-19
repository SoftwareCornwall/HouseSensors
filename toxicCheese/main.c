#include <stdlib.h>
#include <fcntl.h> // for open and flags
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h> //for ioctl
#include <time.h>
#include <stdio.h>

#define READ 0x5F

char * filename = "/dev/i2c-1";

void readBytes(int fd, char buffer[], char offset){
	size_t bytesToRead= 2;
	write(fd, &offset, 1);
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

		int x = 0;
		readBytes(fd, buffer, 0x28);
		int humidity = (buffer[0] << 8); 
		readBytes(fd, buffer, 0x29);
		humidity |= buffer[0];
		
		printf("humidity: %d\n", humidity);
		sleep(3);
		if(x == 10)
			break;
		x++;
	}
	close(fd);
	return 0;
}
