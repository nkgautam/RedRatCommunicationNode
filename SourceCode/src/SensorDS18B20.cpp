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
    float temp;
	int i, j;
    int fd;
	int ret;

	char buf[BUFSIZE];
	char tempBuf[5];
	//while (1){
	fd = open(addr, O_RDONLY);

	if(-1 == fd){
		perror("open device file error");
		return 1;
	}

	while(1){
		ret = read(fd, buf, BUFSIZE);
		if(0 == ret){
			break;
		}
		if(-1 == ret){
			if(errno == EINTR){
				continue;
			}
			perror("read()");
			close(fd);
			return 1;
		}
	}

	for(i=0;i<sizeof(buf);i++){
		if(buf[i] == 't'){
			for(j=0;j<sizeof(tempBuf);j++){
				tempBuf[j] = buf[i+2+j];
			}
		}
	}

	temp = (float)atoi(tempBuf) / 1000;

	close(fd);

	//printf("%.3f C\n",temp);
	return temp;


	//}

}
