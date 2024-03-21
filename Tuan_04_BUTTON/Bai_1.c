#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

#define ON 1
#define OFF 0

int main(int argc, char const *argv[])
{
	/* code */
	int button_fd, fd;
	char buttons[4] = {'0', '0', '0', '0'};
	button_fd = open("/dev/buttons", 0);
	fd = open("/dev/leds", 0);
	int count = 0;
	if(fd < 0){
		perror("open device leds");
		exit(1);
	}
	if(button_fd < 0){
		perror("open device buttons");
		exit(1);
	}
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
				if(buttons[i] == '1')
					ioctl(fd, ON, i);
				else
					ioctl(fd, OFF, i);
				count_of_changed_key++;
			}
		}
		if(count_of_changed_key)
			printf("\n");
	}
	close(fd);
	close(button_fd);
	return 0;
}