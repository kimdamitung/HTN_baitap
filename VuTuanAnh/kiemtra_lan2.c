/*
ban dau pwm 1000hz
btn1: +100hz
btn2: -100hz
btn3: 
	+ x2 btn1
	+ x3 btn1
	+ x1 btn1
btn4:
	+ x2 btn2
	+ x3 btn2
	+ x1 btn2
btn5:
	+ stop pwm
*/
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <linux/fs.h>

#define PWM_IOCTL_SET_FREQ 	1
#define PWM_IOCTL_STOP  	0

void set_buzzer_freq(int fd, int freq){
	int ret = ioctl(fd, PWM_IOCTL_SET_FREQ, freq);
	printf("Freq: %d\n", freq);
	if(ret < 0){
		perror("Set the frequency of the buzzer\n");
		exit(1);
	}
}

int main(int argc, char const *argv[])
{
	/* code */
	int button_fd, led_fd, pwm_fd;
	char buttons[5] = {'0', '0', '0', '0', '0'};
	FILE *pFile;
	button_fd = open("/dev/buttons", 0);
	pwm_fd = open("/dev/pwm", 0);
	/*begin code 0*/
	int btn0 = 0;
	int btn1 = 0;
	int btn2 = 0;
	int btn3 = 0;
	int btn4 = 0;
	/*end code 0*/
	if(button_fd < 0 || pwm_fd < 0)
		perror("Open device (button or led or pwm)!!!\n");
	printf("Open device SUCCESS (^-^)\n");
	/*begin code 1*/
	int freq = 1000;
	set_buzzer_freq(pwm_fd, freq);
	/*end code 1*/
	while(1){
		char current_buttons[5];
		int count_of_changed_key, i;
		if(read(button_fd, current_buttons, sizeof(current_buttons)) != sizeof(current_buttons)){
			perror("read buttons");
			exit(1);
		}for(i = 0, count_of_changed_key = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++){
			if(buttons[i] != current_buttons[i]){
				buttons[i] = current_buttons[i];
				if(buttons[0] == '1')
					btn0 = 1;
				else if(buttons[0] == '0' && btn0 == 1){
					btn0 = 0;
				}
				if(buttons[1] == '1')
					btn1 = 1;
				else if(buttons[1] == '0' && btn1 == 1){
					btn1 = 0;
				}
				if(buttons[2] == '1')
					btn2 = 1;
				else if(buttons[2] == '0' && btn2 == 1){
					btn2 = 0;
				}
				if(buttons[3] == '1')
					btn3 = 1;
				else if(buttons[3] == '0' && btn3 == 1){
					btn3 = 0;
				}
				if(buttons[4] == '1')
					btn4 = 1;
				else if(buttons[4] == '0' && btn4 == 1){
					btn4 = 0;
				}
				count_of_changed_key++;
			}
		}
		if(count_of_changed_key)
			printf("\n");
	}
	close(button_fd);
	close(led_fd);
	close(pwm_fd);
	return 0;
}