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
	int fd, freq = 1000, button_fd;
	fd = open("/dev/pwm", 0);
	char buttons[4] = {'0', '0', '0', '0'};
	button_fd = open("/dev/buttons", 0);
	if(button_fd < 0){
		perror("open device buttons");
		exit(1);
	}
	int ptr, ptr1, ptr2, ptr3;
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
		          	freq += 100;
		        }
		        else if (buttons[1] == '1'){
		        	freq += 50;
		        }
		        else if (buttons[2] == '1'){
		        	freq -= 100;
		        }
		        else if(buttons[3] == '1'){
		        	freq -= 50;
		        }
		        else if(buttons[4] == '1'){
		        	stop_buzzer_freq(fd);
					exit(0);
		        }
		        printf("\tFreq = %d\n", freq);
		        set_buzzer_freq(fd, freq);
				count_of_changed_key++;
			}
		}
		if(count_of_changed_key)
			printf("\n");
	}
	return 0;
}