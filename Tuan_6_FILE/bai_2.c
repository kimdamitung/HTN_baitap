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

int counter_text(FILE *pFile, const char *filename){
	int c;
	int n = 0;
	pFile = fopen (filename,"r");
	if (pFile == NULL)
		perror ("Error opening file");
	else{
 		do{
			c = fgetc (pFile);
			if (c == 'a')
				n++;
		} while (c != EOF);
		fclose (pFile);
		printf ("So chu a xuat hien: %d\n",n);
 	}
 	int state = n % 16;
 	printf("so du cho led: %d", state);
 	return state;
}

void convert_a_to_A(FILE *pFile, const char *filename){
	int c;
	int n = 0;
	pFile = fopen (filename,"r");
	FILE *tempFile;
	tempFile = fopen("temp.txt", "w");
	if(pFile == NULL || tempFile == NULL)
		perror("Error open file!!!!!");
	else{
 		do{
			c = fgetc(pFile);
			if (c == 'a'){
				n++;
				fputc('A', tempFile);
			}else{
				fputc(c, tempFile);
			}
		} while (c != EOF);
 	}
 	printf ("So chu a xuat hien: %d\n",n);
 	fclose (pFile);
	fclose(tempFile);
	pFile = fopen(filename, "w");
	tempFile = fopen("temp.txt", "r");
	while((c = fgetc(tempFile)) != EOF){
		fputc(c, pFile);
	}
	fclose (pFile);
	fclose(tempFile);
	remove("temp.txt");
}

void add_char_in_end_line(FILE *pFile, const char *filename){
	pFile = fopen(filename, "a");
	if(pFile == NULL)
		perror("Error open file");
	int counter = counter_text(pFile, filename);
	fprintf(pFile, "%d", counter);
	fclose(pFile);
}

void display_counter_buttons(FILE *pFile, const char * filename){
	char string[256];
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("error open file");
	else{
		if(fgets(string, 256, pFile) != NULL)
			puts(string);
		fclose(pFile);
	}
}


int main(int argc, char const *argv[])
{
	/* code */
	int couter_button = 0;
	int button_fd, led_fd;
	char buttons[4] = {'0', '0', '0', '0'};
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
		char current_buttons[4];
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
				if(buttons[0] == '1'){
					int state = counter_text(pFile, "input.txt");
					ioctl(led_fd, state & 0x01 ? ON:OFF, 0);
					ioctl(led_fd, state & 0x02 ? ON:OFF, 1);
					ioctl(led_fd, state & 0x04 ? ON:OFF, 2);
					ioctl(led_fd, state & 0x08 ? ON:OFF, 3);
					sleep(2);
				}else if(buttons[1] == '1'){
					convert_a_to_A(pFile, "input.txt");
				}else if(buttons[2] == '1'){
					add_char_in_end_line(pFile, "input.txt");
				}else if(buttons[3] == '1'){
					display_counter_buttons(pFile, "input.txt");
				}
				count_of_changed_key++;
			}

		}
		if(count_of_changed_key)
			printf("\n");
	}
	close(button_fd);
	close(led_fd);
	return 0;
}