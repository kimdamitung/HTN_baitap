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

void display_text_file(FILE *pFile, const char *filename){
	char string[256];
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Error openning file");
	else{
		if(fgets(string, 256, pFile) != NULL)
			puts(string);
		fclose(pFile);
	}
}

int check_number_in_file(FILE *pFile, const char *filename){
	int c;
	int n = 0;
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Error open file!!!");
	while((c = fgetc(pFile)) != EOF){
		if(c >= '0' && c <= '9')
			n++;
	}
	return n;
}

void remove_number_in_file(FILE *pFile, const char *filename){
	pFile = fopen(filename, "r");
	FILE *tempFile = fopen("temp.txt", "w");
	if(pFile == NULL || tempFile == NULL) {
		perror("Error open file!!!!!");
		return;
	}
	int c;
	while((c = fgetc(pFile)) != EOF) {
		if (c < '0' || c > '9') {
			fputc(c, tempFile);
		}
	}
	fclose(pFile);
	fclose(tempFile);
	pFile = fopen(filename, "w");
	tempFile = fopen("temp.txt", "r");
	while((c = fgetc(tempFile)) != EOF) {
		fputc(c, pFile);
	}
	fclose(pFile);
	fclose(tempFile);
	remove("temp.txt");
}

int sum_number_lower_in_end_file(FILE *pFile, const char *filename){
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Erorr open file");
	int c;
	int count_number = 0, count_lower = 0;
	while((c = fgetc(pFile)) != EOF){
		if(c >= '0' && c <= '9')
			count_number++;
		else if(c >= 'a' && c <= 'z')
			count_lower++;
	}
	fclose(pFile);
	return (count_number + count_lower);
}

void add_char_in_end_line(FILE *pFile, const char *filename){
	pFile = fopen(filename, "a");
	if(pFile == NULL)
		perror("Error open file");
	int count = sum_number_lower_in_end_file(pFile, filename);
	fprintf(pFile, "%d", count);
	fclose(pFile);
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
					printf("So lan xuat hien number trong file: %d", check_number_in_file(pFile, "alphabet.txt"));
				}else if(buttons[1] == '1'){
					remove_number_in_file(pFile, "alphabet.txt");
				}else if(buttons[2] == '1'){
					printf("So lan xuat hien cua so va chu thuong trong file:  %d\n", sum_number_lower_in_end_file(pFile, "alphabet.txt"));
					add_char_in_end_line(pFile, "alphabet.txt");
				}else if(buttons[3] == '1'){
					display_text_file(pFile, "alphabet.txt");
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