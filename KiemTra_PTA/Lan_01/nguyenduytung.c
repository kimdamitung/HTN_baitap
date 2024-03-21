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
	int button_fd, fd, pwm_fd, freq = 0;
	char buttons[4] = {'0', '0', '0', '0'};
	pwm_fd = open("/dev/pwm", 0);
	button_fd = open("/dev/buttons", 0);
	fd = open("/dev/leds", 0);
	if(fd < 0){
		perror("open device leds");
		exit(1);
	}
	if(button_fd < 0){
		perror("open device buttons");
		exit(1);
	}
	if(pwm_fd < 0){
		perror("open device buttons");
		exit(1);
	}
	int state = 0;
	while(1){
		char current_buttons[4];
		int count_of_changed_key, i;
		if(read(button_fd, current_buttons, sizeof(current_buttons)) != sizeof(current_buttons)){
			perror("read buttons");
			exit(1);
		}
		ioctl(fd, OFF, 0);
		ioctl(fd, OFF, 1);
		ioctl(fd, OFF, 2);
		ioctl(fd, OFF, 3);

		for(i = 0, count_of_changed_key = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++){
			if(buttons[i] != current_buttons[i]){
				buttons[i] = current_buttons[i];
				printf("%s key %d is %s\n", count_of_changed_key ? ", ":" ", i + 1, buttons[i] == '0' ? "up":"down");
				if (buttons[0] == '1'){
		          	//MSSv 21085061 so gan cuoi so 6 0110
		          	state++;
		          	ioctl(fd, OFF, 0);
					ioctl(fd, ON, 1);
					ioctl(fd, ON, 2);
					ioctl(fd, OFF, 3);
		        }
		        else if (buttons[1] == '1'){
		        	// 4 so cuoi MSSV 5061
		        	ioctl(fd, OFF, 0);
					ioctl(fd, OFF, 1);
					ioctl(fd, OFF, 2);
					ioctl(fd, OFF, 3);
					int count = 0;
					freq = 5061;
					for(count; count < 3; count++){
						set_buzzer_freq(pwm_fd, 5061);
						printf("\tFreq = %d\n", freq);
						usleep(500000);
						ioctl(pwm_fd, PWM_IOCTL_STOP);
						usleep(200000);
					}
		        }
		        else if (buttons[2] == '1'){
		          	int count = 0;
		          	for(count; count < 4; count++){
		          		ioctl(fd, OFF, 0);
						ioctl(fd, ON, 1);
						ioctl(fd, ON, 2);
						ioctl(fd, OFF, 3);
						usleep(500000);
						ioctl(fd, OFF, 0);
						ioctl(fd, OFF, 1);
						ioctl(fd, OFF, 2);
						ioctl(fd, OFF, 3);
						usleep(200000);
		          	}
		        }  
		        else if (buttons[3] == '1'){
		        	close(fd);
					close(button_fd);
					close(pwm_fd);
		        	printf("Close Device\n");
		        	exit(0);
		        }
		        if(state == 2){
		        	ioctl(fd, OFF, 0);
					ioctl(fd, OFF, 1);
					ioctl(fd, OFF, 2);
					ioctl(fd, OFF, 3);
		        	state = 0;
		        }
				count_of_changed_key++;
			}
		}
		if(count_of_changed_key)
			printf("\n");
	}
	close(fd);
	close(button_fd);
	close(pwm_fd);
	return 0;
}