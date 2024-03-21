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
	while(1){
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
	}
	close(fd);
	return 0;
}