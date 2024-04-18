/*
sử dụng kit thực hành nhúng micro friendly ARM 2440 viết chương trình thực hiện các yêu cầu sau:     
1. Viết chương trình ghi 10 ký tự ‘a’ vào file có tên là test.txt
2. Nhấn/nhả K1 để xem file test.txt
3. Nhấn/nhả K2 để sửa nội dung file test.txt thành ‘chao cac ban’
4. Nhập n: (từ 1 -> 5)
Nhấn/nhả K3 chương trình sẽ phát ra n tiếng ở tần số  1000Hz (thời gian delay giữa 2 lần phát là 500ms), đồng thời hiển thị các led tương ứng với giá trị là n: led 0 sáng (n=1), led 0,1 sáng (n=2), led 0,1,2 sáng(n=3), 4 led sáng (n=4), 4 led chớp (n=5).
(mặc định ban đầu 4 led tắt)
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

#define ON  				1
#define OFF 				0
#define PWM_IOCTL_SET_FREQ 	1
#define PWM_IOCTL_STOP  	0

void add_char_in_file(FILE *pFile, const char *filename, const char *text);
void display_file(FILE *pFile, const char *filename);
int state_led(int n);

int main(int argc, char const *argv[])
{
	/* code */
	int button_fd, led_fd, pwm_fd;
	char buttons[3] = {'0', '0', '0'};
	FILE *pFile;
	button_fd = open("/dev/buttons", 0);
	led_fd = open("/dev/leds", 0);
	pwm_fd = open("/dev/pwm", 0);
	/*begin code 0*/
	int btn0 = 0;
	int btn1 = 0;
	int btn2 = 0;
	/*end code 0*/
	if(button_fd < 0 || led_fd < 0 || pwm_fd < 0)
		perror("Open device (button or led or pwm)!!!\n");
	printf("Open device SUCCESS (^-^)\n");
	/*begin code 1*/
	int m;
	for(m = 0; m < 4; m++)
		ioctl(led_fd, OFF, m);
	int n;
	/*end code 1*/
	add_char_in_file(pFile, "test.txt", "aaaaaaaaaa");
	while(1){
		char current_buttons[3];
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
					display_file(pFile, "test.txt");
					btn0 = 0;
				}
				if(buttons[1] == '1')
					btn1 = 1;
				else if(buttons[1] == '0' && btn1 == 1){
					add_char_in_file(pFile, "test.txt", "chao cac ban");
					btn1 = 0;
				}
				if(buttons[2] == '1')
					btn2 = 1;
				else if(buttons[2] == '0' && btn2 == 1){
					do{
						printf("Nhap n: ");
						scanf("%d", &n);
						int j;
						for(j = 0; j < n; j++){
							ioctl(pwm_fd, PWM_IOCTL_SET_FREQ, 1000);
							usleep(500000);
							ioctl(pwm_fd, PWM_IOCTL_STOP);
							usleep(500000);
						}
						if(n == 5){
							ioctl(led_fd, ON, 0);
							ioctl(led_fd, ON, 1);
							ioctl(led_fd, ON, 2);
							ioctl(led_fd, ON, 3);
							usleep(500000);
							ioctl(led_fd, OFF, 0);
							ioctl(led_fd, OFF, 1);
							ioctl(led_fd, OFF, 2);
							ioctl(led_fd, OFF, 3);
							usleep(500000);
						}else{
							int state = state_led(n);
							ioctl(led_fd, (state & 0x01) == 1 ? ON:OFF, 0);
							ioctl(led_fd, (state & 0x03) == 3 ? ON:OFF, 1);
							ioctl(led_fd, (state & 0x07) == 7 ? ON:OFF, 2);
							ioctl(led_fd, (state & 0x0F) == 15 ? ON:OFF, 3);
						}
					}while(n < 1 || n > 5);
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

void add_char_in_file(FILE *pFile, const char *filename, const char *text){
	pFile = fopen(filename, "w");
	if(pFile != NULL)
		fprintf(pFile, "%s ", text);
	fclose(pFile);
}

void display_file(FILE *pFile, const char *filename){
	char string[256];
	pFile = fopen(filename, "r");
	if(pFile != NULL){
		while(fgets(string, 256, pFile) != NULL)
			printf("%s", string);
		printf("\n");
	}
	fclose(pFile);
}

int state_led(int n){
	if(n == 1)
		return 1;
	else if(n == 2)
		return 3;
	else if(n == 3)
		return 7;
	else if(n == 4)
		return 15;
}