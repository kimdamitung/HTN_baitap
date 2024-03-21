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
	int fd, freq = 0, button_fd;
	fd = open("/dev/pwm", 0);
	char buttons[4] = {'0', '0', '0', '0'};
	button_fd = open("/dev/buttons", 0);
	if(button_fd < 0){
		perror("open device buttons");
		exit(1);
	}
	int ptr, ptr1, ptr2, ptr3;
	ptr = 0;
	ptr1 = 0;
	ptr2 = 0;
	ptr3 = 0;
	while(1){
		char current_buttons[4];
		int count_of_changed_key, i;
		if(read(button_fd, current_buttons, sizeof(current_buttons)) != sizeof(current_buttons)){
			perror("read buttons");
			exit(1);
		}
		for(i = 0, count_of_changed_key = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++){
			if(buttons[i] != current_buttons[i]){
				buttons[i] = current_buttons[i];
				printf("%s key %d is %s", count_of_changed_key ? ", ":" ", i + 1, buttons[i] == '0' ? "up":"down");
				if (buttons[0] == '1'){
		          	ptr++;
		          	set_buzzer_freq(fd, 500);
					printf("\tFreq = %d\n", freq);
		        }
		        else if (buttons[1] == '1'){
		          	ptr1++;
		          	set_buzzer_freq(fd, 1000);
					printf("\tFreq = %d\n", freq);
		        }
		        else if (buttons[2] == '1'){
		          	ptr2++;
		          	set_buzzer_freq(fd, 1500);
					printf("\tFreq = %d\n", freq);
		        }
		        else if(buttons[3] == '1'){
		        	stop_buzzer_freq(fd);
					exit(0);
		        }
		        else if(ptr == 2){
		          	ptr = 0;
		          	stop_buzzer_freq(fd);
		        }else if(ptr1 == 2){
		          	ptr1 = 0;
		          	stop_buzzer_freq(fd);
		        }else if(ptr2 == 2){
		          	ptr2 = 0;
		          	stop_buzzer_freq(fd);
				}
				count_of_changed_key++;
			}
		}
		if(count_of_changed_key)
			printf("\n");
	}
	return 0;
}