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
#include <pthread.h>

#define ON  1
#define OFF 0

int led_fd, adc_fd;
static int t = 10;

int stateValue(int value){
	if(value >= 0 && value <= 100){
		return 100;
	}else if(value >= 101 && value <= 200){
		return 200;
	}else if(value >= 201 && value <= 300){
		return 300;
	}else if(value >= 301 && value <= 400){
		return 400;
	}else if(value >= 401 && value <= 500){
		return 500;
	}else if(value >= 501 && value <= 600){
		return 600;
	}else if(value >= 601 && value <= 700){
		return 700;
	}else if(value >= 701 && value <= 800){
		return 800;
	}else if(value >= 801 && value <= 900){
		return 900;
	}else if(value >= 901 && value <= 1000){
		return 1000;
	}else if(value >= 1001 && value <= 1023){
		return 1100;
	}
}

void *led_polling(void *param);

int main(int argc, char const *argv[])
{
	/* code */
	int i;
	adc_fd = open("/dev/adc", 0);
	led_fd = open("/dev/leds", 0);
	if(led_fd < 0 || adc_fd < 0){
		perror("Open device (led or adc)");
		exit(1);
	}else{
		printf("Open device SUCCESS\n");
	}
	const char *thread_parms = "button thread";
	pthread_t thread_id;
	thread_id = pthread_create(&thread_id, NULL, &led_polling, (void*)thread_parms);
	while(1){
		char buffer[30];
		int len = read(adc_fd, buffer, sizeof(buffer)- 1);
		if(len > 0){
			buffer[len] = '\0';
			int value = -1;
			sscanf(buffer, "%d", &value);
			printf("ADC Value: %d\n", value);
			t = stateValue(value);
		}
	}
	close(led_fd);
	close(adc_fd);
	return 0;
}

void *led_polling(void *param){
	int len_on = 0;
	for(;;){
		if(len_on == 4){
			len_on = 0;
			ioctl(led_fd, OFF, 0);
			ioctl(led_fd, OFF, 1);
			ioctl(led_fd, OFF, 2);
			ioctl(led_fd, OFF, 3);
		}
		ioctl(led_fd, ON, len_on);
		len_on++;
		printf("Time out on led: %d\n", t);
		usleep(1000 * t);
	}
}