#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <pthread.h>

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

void sleepms(int ms){
	usleep(1000 * ms);
	return;
}

int pwm_fd, button_fd;

static int t = 1000;

void *pwm_polling(void *param);

int main(int argc, char const *argv[])
{
	/* code */
	int led_no;
	char buttons[6] = {'0', '0', '0', '0', '0', '0'};
	int i;
	pwm_fd = open("/dev/pwm", 0);
	button_fd = open("/dev/buttons", 0);
	if(pwm_fd < 0 || button_fd < 0){
		perror("open device (pwm or buttons)");
		exit(1);
	}else{
		printf("Open device SUCCESS\n");
	}
	const char *thread_parms = "button thread";
	pthread_t thread_id;
	thread_id = pthread_create(&thread_id, NULL, &pwm_polling, (void*)thread_parms);
	int freq = 500;
	while(1){
		if(freq > 3000)
			freq = 500;
		set_buzzer_freq(pwm_fd, freq);
		printf("\tFreq = %d\n", freq);
		sleepms(t);
		freq += 100;

	}
	close(button_fd);
	close(pwm_fd);
	return 0;
}

void *pwm_polling(void *param){
	char cur_btn[3], old_btn[3] = {'0', '0', '0'};
	int i;
	for(;;){
		int num = read(button_fd, cur_btn, sizeof(cur_btn));
		if(num != sizeof(cur_btn)){
			perror("read buttons");
			exit(1);
		}
		if(old_btn[0] != cur_btn[0]){
			sleepms(300);
			old_btn[0] = cur_btn[0];
			t = t + 50;
			printf("Key 1 is pressed/released t = %d ms\n", t);
		}
		if(old_btn[1] != cur_btn[1]){
			sleepms(300);
			old_btn[1] = cur_btn[1];
			t = t - 50;
			printf("Key 2 is pressed/released t = %d ms\n", t);
			if(t < 100)
				t = 100;
		}
		if(old_btn[2] != cur_btn[2]){
			sleepms(300);
			old_btn[2] = cur_btn[2];
			stop_buzzer_freq(pwm_fd);
		}
	}
}