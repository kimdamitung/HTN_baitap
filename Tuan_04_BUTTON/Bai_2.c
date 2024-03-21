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
	int ptr, ptr1, ptr2, ptr3;
	ptr = 0;
	ptr1 = 0;
	ptr2 = 0;
	ptr3 = 0;
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
				if (buttons[0] == '1'){
		          	ptr++;
		          	ioctl(fd, ON, 0);
		        }
		        else if (buttons[1] == '1'){
		          	ptr1++;
		          	ioctl(fd, ON, 1);
		        }
		        else if (buttons[2] == '1'){
		          	ptr2++;
		          	ioctl(fd, ON, 2);
		        }
		        else if (buttons[3] == '1'){
		          	ptr3++;
		          	ioctl(fd, ON, 3);
		        }  
		        else if(ptr == 2){
		          	ioctl(fd, OFF, 0);
		          	ptr = 0;
		        }else if(ptr1 == 2){
		          	ioctl(fd, OFF, 1);
		          	ptr1 = 0;
		        }else if(ptr2 == 2){
		          	ioctl(fd, OFF, 2);
		          	ptr2 = 0;
		        }else if(ptr3 == 2){
		          	ioctl(fd, OFF, 3);
		          	ptr3 = 0;
		        }
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