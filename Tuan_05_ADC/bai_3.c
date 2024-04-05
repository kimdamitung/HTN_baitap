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
#include <termios.h>

#define ON 1
#define OFF 0
#define PWM_IOCTL_SET_FREQ 1
#define PWM_IOCTL_STOP 0
#define ESC_KEY 0x1b

void set_buzzer_freq(int fd, int freq){
	int ret = ioctl(fd, PWM_IOCTL_SET_FREQ, freq);
	if(ret < 0){
		perror("Set the frequency of the buzzer\n");
		exit(1);
	}
}

void stop_buzzer_freq(int fd){
	int ret = ioctl(fd, PWM_IOCTL_STOP);
	if(ret < 0){
		perror("Stop the buzzer\n");
		exit(1);
	}
	close(fd);
}

int main(int argc, char const *argv[])
{
	/* code */
	printf("Press Ctrl-C to stop\n"); 
 	int adc_fd = open("/dev/adc", 0);
 	int fd = open("/dev/leds", 0); 
	int pwm_fd = open("/dev/pwm", 0);
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
			set_buzzer_freq(pwm_fd, value);
 		}else { 
 			perror("read ADC device:"); 
 			return 1; 
 		}
 		usleep(500 * 1000); 
 	} 
 	close(fd); 
	return 0;
}