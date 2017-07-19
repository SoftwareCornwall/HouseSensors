#include <stdlib.h>
#include <fcntl.h> // for open and flags
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h> //for ioctl
#include <time.h>
#include <stdio.h>

#define READ 0x5F

int main(int argc, char *argv[]){
	char * filename = "/dev/i2c-1";
	char *outputFile = "~/.humidity";
	char buffer[20];
	int fd = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0){
		printf("could not open: %s", filename);
		exit(1);	
	}
	if(ioctl(fd, I2C_SLAVE, READ)){
		printf("error setting up i2c port");
		exit(1);	
	}
	size_t bytesToRead = 1;
	size_t bytesRead = read(fd, buffer, bytesToRead);
	
	if(bytesRead != bytesToRead){
		printf("error reading from: %s", filename);
		close(fd);
		exit(1);
	}
	printf("humidity: %s\n", buffer);
	
	close(fd);
	return 0;
}
