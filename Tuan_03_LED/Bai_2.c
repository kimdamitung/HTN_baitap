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
	int fd;
	fd = open("/dev/leds", 0);
	if(fd < 0){
		perror("open device leds");
		exit(1);
	}
	int state = 0;
	while(1){
		ioctl(fd, state & 0x01 ? ON:OFF, 0);
		ioctl(fd, state & 0x02 ? ON:OFF, 1);
		ioctl(fd, state & 0x04 ? ON:OFF, 2);
		ioctl(fd, state & 0x08 ? ON:OFF, 3);
		usleep(300000);
		state++;
		if(state > 16)
			state = 0;
	}
	close(fd);
	return 0;
}