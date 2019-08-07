#include "SensorDS18B20.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define  BUFSIZE  128

char* addr = "/sys/bus/w1/devices/28-00043ce370ff/w1_slave";
using namespace std;

SensorDS18B20::SensorDS18B20()
{
    //ctor
}

float
SensorDS18B20::GetReading()
{
    float fTemperature;
	int iCounter, jCounter;
    int fileDescriptor;
	int retValue;

	char charBuffer[BUFSIZE];
	char tempBuf[5];

	fileDescriptor = open(addr, O_RDONLY);

	if(-1 == fileDescriptor){
		perror("open device file error");
		return 1;
	}

	while(1){
		retValue = read(fileDescriptor, charBuffer, BUFSIZE);
		if(0 == retValue){
			break;
		}
		if(-1 == retValue){
			if(errno == EINTR){
				continue;
			}
			perror("read()");
			close(fileDescriptor);
			return 1;
		}
	}

	for(iCounter=0;iCounter<sizeof(charBuffer);iCounter++){
		if(charBuffer[iCounter] == 't'){
			for(jCounter=0;jCounter<sizeof(tempBuf);jCounter++){
				tempBuf[jCounter] = charBuffer[iCounter+2+jCounter];
			}
		}
	}

	fTemperature = (float)atoi(tempBuf) / 1000;

	close(fileDescriptor);

	return fTemperature;

}
