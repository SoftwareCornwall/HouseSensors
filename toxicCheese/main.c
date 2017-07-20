#include <stdlib.h>
#include <fcntl.h> // for open and flags
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h> //for ioctl
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include "main.h"

#define READ 0x5F

char * filename = "/dev/i2c-1";
int fd = 0;

int accurateHumidity(int16_t humidity, int16_t H0_T0_OUT, int16_t H1_T0_OUT, uint8_t rH0, uint8_t rH1){
	int H_OUT = (humidity - H0_T0_OUT) * (rH1 - rH0);
	H_OUT /= (H1_T0_OUT - H0_T0_OUT);
	H_OUT += rH0;

	return H_OUT;
}
void readBytes(char buffer[], char offset){
	size_t bytesToRead = 1;
	puts("writing");
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
int shift(char buffer[], int offset){
	int returnValue = 0;
	readBytes(buffer, offset);
	returnValue = buffer[0];
	if(offset == HUMIDITY_OUT_H)
		printf("return Value:%x\n",returnValue);
#ifdef DEBUG
	printf("\nreturn value for %x: %x\n", offset, returnValue);
#endif
	returnValue =returnValue <<  8;
	readBytes(buffer, offset - 1);
	returnValue |= buffer[0];
	if(offset == HUMIDITY_OUT_H)
		printf("return Value:%x\n", returnValue);
#ifdef DEBUG
	printf("return value: %x\n", returnValue);
#endif
	return returnValue;
}
void init(void){
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
}

int main(int argc, char *argv[]){
	//char *outputFile = "~/.humidity";
	char *buffer;
	int humidity = 0; 
	int H0_T0_OUT = 0;
	int16_t H1_T0_OUT = 0;
	uint8_t rH0 = 0;
	uint8_t rH1 = 0;
	int H_OUT;

	init();

	H0_T0_OUT = shift(buffer, H0_T0_OUT_H);
	H1_T0_OUT = shift(buffer, H1_T0_OUT_H);

	rH0 = shift(buffer, H0_rH_x2);
	rH1 = shift(buffer, H1_rH_x2);
	printf("rH0: 0x%x\nrH1: 0x%x\n", rH0, rH1);
	printf("H0: 0x%x\nH1: 0x%x\n",H0_T0_OUT, H1_T0_OUT);
	while(1){

		int humidity = 0; 
		puts("reading bytes");
#ifdef DEBUG
		readBytes(buffer, WHO_AM_I);
		readBytes(buffer, AV_CONF);
		readBytes(buffer, CTRL_REG1);
		readBytes(buffer, CTRL_REG2);
		readBytes(buffer, CTRL_REG3);
		readBytes(buffer, STATUS_REG);
		readBytes(buffer, HUMIDITY_OUT_L);
		readBytes(buffer, HUMIDITY_OUT_H);
		readBytes(buffer, TEMP_OUT_L);
		readBytes(buffer, TEMP_OUT_H);
#endif
		humidity = shift(buffer, HUMIDITY_OUT_H);

		H_OUT = accurateHumidity(humidity, H0_T0_OUT, H1_T0_OUT, rH1, rH0);

		printf("humidity: %x\n", humidity);
		printf("H_OUT: %d\n", H_OUT);
		printf("test humidity: %d\n", accurateHumidity(0x5000, 0x4000, 0x6000, 20, 40));
		sleep(3);
	}
	close(fd);
	return 0;
}
