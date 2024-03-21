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
	int bits = 0;
	fd = open("/dev/leds", 0);
	if(fd < 0){
		perror("open device leds");
		exit(1);
	}
	ioctl(fd, OFF, 0);
	ioctl(fd, OFF, 1);
	ioctl(fd, OFF, 2);
	ioctl(fd, OFF, 3);
	printf("Nhan phim 1 de 4 leds duoi theo chu ky\n");
	printf("Nhan phim 2 de 4 led sang tat theo chu ky\n");
	printf("Nhan phim 3 de dung trang thai dang chay\n");
	while(1){
		key = getchar();
		sleep(1);
		switch(key){
			case '1':
				for(bits = 0;bits < 4; bits++){
          			ioctl(fd, (1 << bits) & 0x01 ? ON:OFF, 0);
				  	ioctl(fd, (1 << bits) & 0x02 ? ON:OFF, 1);
				  	ioctl(fd, (1 << bits) & 0x04 ? ON:OFF, 2);
				  	ioctl(fd, (1 << bits) & 0x08 ? ON:OFF, 3);
				  	usleep(300000);
        		}
        		ioctl(fd, OFF, 0);
				ioctl(fd, OFF, 1);
				ioctl(fd, OFF, 2);
				ioctl(fd, OFF, 3);
				break;
			case '2':
				ioctl(fd, ON, 0);
				ioctl(fd, ON, 1);
				ioctl(fd, ON, 2);
				ioctl(fd, ON, 3);
				usleep(500000);
				ioctl(fd, OFF, 0);
				ioctl(fd, OFF, 1);
				ioctl(fd, OFF, 2);
				ioctl(fd, OFF, 3);
				usleep(500000);
				break;
			case '3':
				ioctl(fd, OFF, 0);
				ioctl(fd, OFF, 1);
				ioctl(fd, OFF, 2);
				ioctl(fd, OFF, 3);
				break;
		}
	}
	close(fd);
	return 0;
}