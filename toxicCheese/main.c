#include <stdlib.h>
#include <fcntl.h> // for open and flags
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h> //for ioctl
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "main.h"

#define READ 0x5F

char * filename = "/dev/i2c-1";

int accurateHumidity(int humidity, int16_t H0_T0_OUT, int16_t H1_T0_OUT, uint8_t rH0, uint8_t rH1){
	double ratio = (rH1 - rH0) / (H1_T0_OUT - H0_T0_OUT);
	int H_OUT = (humidity - H0_T0_OUT) * ratio + rH0;

	return H_OUT;
}
void readBytes(int fd, char buffer[], char offset){
	size_t bytesToRead = 1;
	write(fd, &offset, 1);
	size_t bytesRead = read(fd, buffer, bytesToRead);
	if(bytesRead != bytesToRead){
		printf("error reading from: %s\n", filename);
		close(fd);
		exit(1);
	}
	//printf("%X: %X\n",offset, buffer[0]);
}

//call shift with the higher byte
int shift(int fd, char buffer[], int offset){
	int returnValue = 0;
	readBytes(fd, buffer, offset);
	returnValue = buffer[0];
#ifdef DEBUG
	printf("\nreturn value for %x: %x\n", offset, returnValue);
#endif
	returnValue =returnValue <<  8;
	readBytes(fd, buffer, offset-1);
	returnValue |= buffer[0];
#ifdef DEBUG
	printf("return value: %x\n", returnValue);
#endif
	return returnValue;
}
int init(void){
	int fd = 0;
	puts("opening file");
	fd = open(filename, O_RDWR);
	if (fd < 0){
		fprintf(stderr, "could not open: %s\n", filename);
		exit(1);	
	}
	puts("setting up i2c port");

	if(ioctl(fd, I2C_SLAVE, READ)){
		fprintf(stderr, "error setting up i2c port\n");
		exit(1);	
	}
	return fd;
}

int main(int argc, char *argv[]){
	char *outputFile = "~/.humidity";
	char *buffer;
	int fd = init();
	int humidity = 0; 
	int16_t H0_T0_OUT = 0;
	int H1_T0_OUT = 0;
	uint8_t rH0 = 0;
	uint8_t rH1 = 0;

	H0_T0_OUT = shift(fd, buffer, H0_T0_OUT_H);
	H1_T0_OUT = shift(fd, buffer, H1_T0_OUT_H);

	rH0 = shift(fd, buffer, H0_rH_x2);
	rH1 = shift(fd, buffer, H1_rH_x2);
	printf("rH0: 0x%x\nrH1: 0x%x\n", rH0, rH1);
	printf("H0: 0x%x\nH1: 0x%x\n",H0_T0_OUT, H1_T0_OUT);
	while(1){

		int x = 0;
		puts("reading bytes");
#ifdef DEBUG
		readBytes(fd, buffer, WHO_AM_I);
		readBytes(fd, buffer, AV_CONF);
		readBytes(fd, buffer, CTRL_REG1);
		readBytes(fd, buffer, CTRL_REG2);
		readBytes(fd, buffer, CTRL_REG3);
		readBytes(fd, buffer, STATUS_REG);
		readBytes(fd, buffer, HUMIDITY_OUT_L);
		readBytes(fd, buffer, HUMIDITY_OUT_H);
		readBytes(fd, buffer, TEMP_OUT_L);
		readBytes(fd, buffer, TEMP_OUT_H);
#endif


		humidity = shift(fd, buffer, HUMIDITY_OUT_H);
		int H_OUT = accurateHumidity(humidity, H0_T0_OUT, H1_T0_OUT, rH0, rH1);
		printf("humidity: %x\n", humidity);
		printf("H_OUT: %d\n", H_OUT);

		sleep(3);
	}
	close(fd);
	return 0;
}
