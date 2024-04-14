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

void display_file(FILE *pFile, const char *filename){
	char string[256];
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Error open file\n");
	while(fgets(string, 256, pFile) != NULL)
		printf("%s", string);
	printf("\n");
	fclose(pFile);
}


void add_char_in_file(FILE *pFile, const char *filename, const char *text){
	pFile = fopen(filename, "w");
	if(pFile != NULL)
		fprintf(pFile, "%s\n", text);
	fclose(pFile);
}

int check_number_in_file(FILE *pFile, const char *filename){
	int c, n = 0;
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Error open file");
	while((c = fgetc(pFile)) != EOF)
		if(c >= '0' && c <= '9')
			n++;
	fclose(pFile);
	return n;
}

int check_text_in_file(FILE *pFile, const char *filename){
	int c, n = 0, m = 0;
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Error open file");
	while((c = fgetc(pFile)) != EOF){
		if(c >= 'a' && c <= 'z' )
			n++;
		else if(c >= 'A' && c <= 'Z')
			m++;
	}
	fclose(pFile);
	return (n + m);
}

void append_char_position(FILE *pFile, const char *filename, int position, const char *text){
	pFile = fopen(filename, "r");
	FILE *tempFile = fopen("temp.txt", "w");
	if(pFile == NULL || tempFile == NULL)
		perror("Error open file");
	int c, counter = 0;
	int i;
	while((c = fgetc(pFile)) != EOF){
		if (counter == position) {
            int i = 0;
            while (text[i] != '\0') {
                fputc(text[i], tempFile);
                i++;
            }
        }
        fputc(c, tempFile);
        counter++;
	}
	fclose(pFile);
	fclose(tempFile);
	pFile = fopen(filename, "w");
	tempFile = fopen("temp.txt", "r");
	while((c = fgetc(tempFile)) != EOF) 
		fputc(c, pFile);
	fclose(pFile);
	fclose(tempFile);
	remove("temp.txt");
}

int main(int argc, char const *argv[])
{
	/* code */
	int couter_button = 0;
	int button_fd, led_fd, pwm_fd;
	char buttons[4] = {'0', '0', '0', '0'};
	FILE *pFile;
	button_fd = open("/dev/buttons", 0);
	led_fd = open("/dev/leds", 0);
	pwm_fd = open("/dev/pwm", 0);
	if(led_fd < 0){
		perror("open device leds");
		exit(1);
	}
	if(button_fd < 0){
		perror("open device buttons");
		exit(1);
	}
	while(1){
		char current_buttons[4];
		int count_of_changed_key;
		int i;
		int freq;
		int btn1, btn2, btn3;
		ioctl(led_fd, OFF, 0);
		ioctl(led_fd, OFF, 1);
		ioctl(led_fd, OFF, 2);
		ioctl(led_fd, OFF, 3);
		if(read(button_fd, current_buttons, sizeof(current_buttons)) != sizeof(current_buttons)){
			perror("read buttons");
			exit(1);
		}
		for(i = 0, count_of_changed_key = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++){
			if(buttons[i] != current_buttons[i]){
				buttons[i] = current_buttons[i];
				printf("%s key %d is %s", count_of_changed_key ? ", ":" ", i + 1, buttons[i] == '0' ? "up\n":"down\n");
				if(buttons[0] == '1'){
					ioctl(led_fd, ON, 0);
					ioctl(led_fd, OFF, 1);
					ioctl(led_fd, OFF, 2);
					ioctl(led_fd, OFF, 3);
					for(btn1 = 0; btn1 < 2; btn1++){
						set_buzzer_freq(pwm_fd, 1000);
						usleep(200000);
						ioctl(pwm_fd, PWM_IOCTL_STOP);
						usleep(300000);
					}
					ioctl(pwm_fd, PWM_IOCTL_STOP);
					const char *text = "Nguyen Duy Tung ";
					add_char_in_file(pFile, "hoten.txt", text);
				}	
				else if(buttons[1] == '1'){
					ioctl(led_fd, OFF, 0);
					ioctl(led_fd, ON, 1);
					ioctl(led_fd, OFF, 2);
					ioctl(led_fd, OFF, 3);
					for(btn2 = 0; btn2 < 3; btn2++){
						set_buzzer_freq(pwm_fd, 2000);
						usleep(100000);
						ioctl(pwm_fd, PWM_IOCTL_STOP);
						usleep(100000);
					}
					ioctl(pwm_fd, PWM_IOCTL_STOP);
					// add_number_end_line(pFile, "hoten.txt", 21085061);
					append_char_position(pFile, "hoten.txt", 15, " 21085061");
				}	
				else if(buttons[2] == '1'){
					ioctl(led_fd, OFF, 0);
					ioctl(led_fd, OFF, 1);
					ioctl(led_fd, ON, 2);
					ioctl(led_fd, OFF, 3);
					for(btn3 = 0; btn3 < 3; btn3++){
						set_buzzer_freq(pwm_fd, 3000);
						usleep(200000);
						ioctl(pwm_fd, PWM_IOCTL_STOP);
						usleep(100000);
					}
					ioctl(pwm_fd, PWM_IOCTL_STOP);
					printf("So ki tu so: %d\n", check_number_in_file(pFile, "hoten.txt"));
					printf("So ki tu so: %d\n", check_text_in_file(pFile, "hoten.txt"));
				}
				else if(buttons[3] == '1'){
					display_file(pFile, "hoten.txt");
					stop_buzzer_freq(pwm_fd);
				}
				count_of_changed_key++;
			}

		}
		if(count_of_changed_key)
			printf("\n");
	}
	close(button_fd);
	return 0;
}