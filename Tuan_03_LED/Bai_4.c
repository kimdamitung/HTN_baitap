#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ON 1
#define OFF 0

int main(int argc, char const *argv[])
{
	/* code */
	int fd, i;
	char key = 0xff;
	int status_leds[4] = {0, 0, 0, 0};
	fd = open("/dev/leds", 0);
	if(fd < 0){
		perror("open device leds");
		exit(1);
	}
	ioctl(fd, OFF, 0);
	ioctl(fd, OFF, 1);
	ioctl(fd, OFF, 2);
	ioctl(fd, OFF, 3);
	printf("Nhan phim s de xem trang thai led\n");
	printf("Nhan phim r de tat cac led\n");
	printf("Nhan phim 0, 1, 2, 3 de dao trang thai cac led\n");
	while(1){
		key = getchar();
		sleep(1);
		switch(key){
			case 'r':
				printf("Cac led deu OFF:\n");
				ioctl(fd, OFF, 0);
				ioctl(fd, OFF, 1);
				ioctl(fd, OFF, 2);
				ioctl(fd, OFF, 3);
				break;
			case 's':
				printf("Trang thai cac leds:\n");
				printf("Led 0: %s", status_leds[0] == 0 ? "OFF":"ON");
				printf("Led 1: %s", status_leds[1] == 0 ? "OFF":"ON");
				printf("Led 2: %s", status_leds[2] == 0 ? "OFF":"ON");
				printf("Led 3: %s", status_leds[3] == 0 ? "OFF":"ON");
				break;
			case '0':
				status_leds[0] = (status_leds[0] + 1) % 2;
				ioctl(fd, status_leds[0], 0);
				printf("Led 0: %s\n", status_leds[0] == 0 ? "OFF":"ON");
				break;
			case '1':
				status_leds[1] = (status_leds[1] + 1) % 2;
				ioctl(fd, status_leds[1], 1);
				printf("Led 1: %s\n", status_leds[1] == 0 ? "OFF":"ON");
				break;
			case '2':
				status_leds[2] = (status_leds[2] + 1) % 2;
				ioctl(fd, status_leds[2], 2);
				printf("Led 2: %s\n", status_leds[2] == 0 ? "OFF":"ON");
				break;
			case '3':
				status_leds[3] = (status_leds[3] + 1) % 2;
				ioctl(fd, status_leds[3], 3);
				printf("Led 3: %s\n", status_leds[3] == 0 ? "OFF":"ON");
				break;
		}
	}
	close(fd);
	return 0;
}