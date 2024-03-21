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
	int ptr0, ptr1, ptr2, ptr3;
	ptr0 = 0;
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
		ioctl(fd, OFF, 0);
		ioctl(fd, OFF, 1);
		ioctl(fd, OFF, 2);
		ioctl(fd, OFF, 3);
		for(i = 0, count_of_changed_key = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++){
			if(buttons[i] != current_buttons[i]){
				buttons[i] = current_buttons[i];
				printf("%s key %d is %s", count_of_changed_key ? ", ":" ", i + 1, buttons[i] == '0' ? "up":"down");
				if (buttons[0] == '1'){
		          	while(ptr0 < 3){
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
		            	ptr0++;
			        }
			        ptr0 = 0;
		        }
		        if (buttons[1] == '1'){
		          	int bits = 1;
          			int count;
          			for(count = 0; count < 12; count++){
            			ioctl(fd, (bits << ptr1) & 0x01 ? ON:OFF, 0);
					  	ioctl(fd, (bits << ptr1) & 0x02 ? ON:OFF, 1);
					  	ioctl(fd, (bits << ptr1) & 0x04 ? ON:OFF, 2);
					  	ioctl(fd, (bits << ptr1) & 0x08 ? ON:OFF, 3);
            			usleep(500000);
					  	ptr1++;
            			if(ptr1 > 3){
              				ptr1 = 0;
            			}
          			}
          			ioctl(fd, OFF, 0);
		      		ioctl(fd, OFF, 1);
		      		ioctl(fd, OFF, 2);
		      		ioctl(fd, OFF, 3);
		        }
		        if (buttons[2] == '1'){
		          	for(ptr2; ptr2 < 16; ptr2++){
            			ioctl(fd, ptr2 & 0x01 ? ON:OFF, 0);
					  	ioctl(fd, ptr2 & 0x02 ? ON:OFF, 1);
					  	ioctl(fd, ptr2 & 0x04 ? ON:OFF, 2);
					  	ioctl(fd, ptr2 & 0x08 ? ON:OFF, 3);
            			usleep(500000);
          			}
          			ioctl(fd, OFF, 0);
		      		ioctl(fd, OFF, 1);
		      		ioctl(fd, OFF, 2);
		     		ioctl(fd, OFF, 3);
		        }  
		        if (buttons[3] == '1'){
		        	int a[4] = {1, 3, 7, 15};
          			int *contro;
          			contro = a;
          			int number_led = 0;
          			while(contro < a + 4){
            			ioctl(fd, *contro ? ON:OFF, number_led);
            			contro++;
            			number_led++;
            			usleep(500000);
          			}
          			ioctl(fd, OFF, 0);
		      		ioctl(fd, OFF, 1);
		      		ioctl(fd, OFF, 2);
		     		ioctl(fd, OFF, 3);
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