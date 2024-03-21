#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <linux/fs.h>
#include <string.h>

#define ON 1
#define OFF 0

int stateLED(int value){
	if(value >= 0 && value < 128){
		return 0;
	}else if(value >= 128 && value < 256){
		return 1;
	}else if(value >= 256 && value < 512){
		return 2;
	}else if(value >= 512 && value < 1023){
		return 3;
	}
}

int main(int argc, char const *argv[])
{
	/* code */
	printf("Press Ctrl-C to stop\n"); 
 	int adc_fd = open("/dev/adc", 0);
 	int fd = open("/dev/leds", 0); 
 	if (adc_fd < 0) { 
 		perror("open ADC device:"); 
 		return 1; 
 	}
 	if (fd < 0) { 
 		perror("open LED device:"); 
 		return 1; 
 	}
 	while(1) { 
 		char buffer[30]; 
 		int len = read(adc_fd, buffer, sizeof(buffer)-1); 
 		if (len > 0){ 
 			buffer[len] = '\0'; 
 			int value = -1; 
 			sscanf(buffer, "%d", &value);//doc du lieu theo dinh dang 
 			printf("ADC Value: %d\n", value);
 			int stateValue = stateLED(value);
			ioctl(fd, stateValue == 0 ? ON:OFF, 0);
			ioctl(fd, stateValue == 1 ? ON:OFF, 1);
			ioctl(fd, stateValue == 2 ? ON:OFF, 2);
			ioctl(fd, stateValue == 3 ? ON:OFF, 3); 
 		}else { 
 			perror("read ADC device:"); 
 			return 1; 
 		}
 		usleep(500* 1000); 
 	} 
 	close(fd); 
	return 0;
}