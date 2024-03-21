#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	int fd, freq = 20;
	fd = open("/dev/pwm", 0);
	if(fd < 0){
		perror("open pwm buzzer device\n");
		exit(1);
	}
	while(1){
		set_buzzer_freq(fd, freq);
		printf("\tFreq = %d\n", freq);
		sleep(1);
		freq += 10;
		if(freq == 50){
			stop_buzzer_freq(fd);
			exit(0);
		}
	}
	return 0;
} 