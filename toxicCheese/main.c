#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <time.h>

#define READ 0x5F

int main(int argc, char *argv[]){
	char * filename = "/dev/i2c-1";
	char buffer[20];
	int fd = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0){
		puts("could not open: %s", filename);
		exit(1);	
	}
	size_t bytesToRead = 4;
	size_t bytesRead = read(fd, buffer, bytesToRead);
	
	if(bytesRead != bytesRead){
		puts("error reading from: %s", filename);
		close(fd);
		exit(1);
	}
	
	close(fd);
	return 0;
}
