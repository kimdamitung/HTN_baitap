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

void putext_interger_counter_buttons(FILE *pFile, const char *filename, int counter){
	pFile = fopen(filename, "w");
	if(pFile != NULL){
		fprintf(pFile, "%d", counter);
		fclose(pFile);
	}
}

void display_counter_buttons(FILE *pFile, const char * filename){
	char string[10];
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("error open file");
	else{
		if(fgets(string, 10, pFile) != NULL)
			puts(string);
		fclose(pFile);
	}
}

int main(int argc, char const *argv[])
{
	/* code */
	int couter_button = 0;
	int button_fd, led_fd;
	char buttons[3] = {'0', '0', '0'};
	FILE *pFile;
	button_fd = open("/dev/buttons", 0);
	led_fd = open("/dev/leds", 0);
	if(led_fd < 0){
		perror("open device leds");
		exit(1);
	}
	if(button_fd < 0){
		perror("open device buttons");
		exit(1);
	}
	while(1){
		char current_buttons[3];
		int count_of_changed_key;
		int i;
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
				if(buttons[0] == '1')
					couter_button++;
				else if(buttons[1] == '1')
					display_counter_buttons(pFile, "input.txt");
				else if(buttons[2] == '1')
					couter_button = 0;
				putext_interger_counter_buttons(pFile, "input.txt", couter_button);
				count_of_changed_key++;
			}

		}
		if(count_of_changed_key)
			printf("\n");
	}
	close(button_fd);
	return 0;
}