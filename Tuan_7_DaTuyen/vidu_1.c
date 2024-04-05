//led button thread
#include <pthread.h>
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

#define ON  1
#define OFF 0

int led_fd, button_fd;
static int t = 1000;

void sleepms(int ms){
	usleep(1000 * ms);
	return;
}

void *btn_polling(void *param);

int main(int argc, char const *argv[])
{
	/* code */
	const char *thread_parms = "button thread";
	pthread_t thread_id;
	int led_no;
	char buttons[6] = {'0', '0', '0', '0', '0', '0'};
	int i;
	led_fd = open("/dev/leds", 0);
	button_fd = open("/dev/buttons", 0);
	if(led_fd < 0 || button_fd < 0){
		perror("open device (led or buttons)");
		exit(1);
	}else{
		printf("Open device SUCCESS\n");
	}
	thread_id = pthread_create(&thread_id, NULL, &btn_polling, (void*)thread_parms);
	for(i = 0; i < 4; i++)
		ioctl(led_fd, OFF, i);
	led_no = 0;
	while(1){
		ioctl(led_fd, ON, led_no);
		sleepms(t);
		ioctl(led_fd, OFF, led_no);
		led_no++;
		if(led_no == 4)
			led_no = 0;
	}
	close(button_fd);
	close(led_fd);
	return 0;
}

void *btn_polling(void *param){
	char cur_btn[2], old_btn[2] = {'0', '0'};
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
		}
	}
}