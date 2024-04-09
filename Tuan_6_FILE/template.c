#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h> 
#include <unistd.h>

int buttons_fd;
char buttons[4] = {'0', '0', '0', '0'};
// moi 
int k1_pre = 0;
int k2_pre = 0;
int count = 0;

int main(int argc, char** argv)
{	
	buttons_fd = open("/dev/buttons", 0);
 	if (buttons_fd < 0)
	{
 		perror("open device buttons");
 		exit(1);
 	}
 	while(1) 
 	{
 		char current_buttons[4];
 		
 		int i;
 		//Đọc trạng thái các nút bấm
 		if (read(buttons_fd, current_buttons, sizeof current_buttons) != sizeof current_buttons)
		{
 			perror("read buttons:");
 			exit(1);
 		}
 		//Kiểm tra trạng thái các nút bấm và in ra trạng thái phù hợp (Key up hay Key down)
 		for (i = 0; i < sizeof buttons / sizeof buttons[0]; i++)
		{
			if (buttons[i] != current_buttons[i])
			{
 				buttons[i] = current_buttons[i];
 				if(buttons[0] == '1' )
				{	
					k1_pre++;
				}
				else if(buttons[1] == '1')
				{	
					k2_pre++;
				}
				else if(buttons[0] == '0' && k1_pre != 0)
				{
					FILE * pFile;
					pFile = fopen ("K1.txt","w");
					count++;
					//luu file 
					fprintf(pFile, "%d", count);
					fclose (pFile);	
				}
				else if(buttons[1] == '0' && k2_pre == 1)
				{
					FILE * pFile;
					pFile = fopen ("K1.txt","r");
					//
					char buffer[1];
					fread(buffer, 1, 1, pFile);
					printf("So lan nhat nut K1 la:%s\n", buffer);
					fclose(pFile);
				}
				else if(buttons[2] == '1')
				{
					FILE * pFile;
					pFile = fopen ("K1.txt","w");
					count = 0;
					fprintf(pFile, "%d", count);
					fclose(pFile);
				}
 			}
 		}
 	}
 	close(buttons_fd);
 	return 0;
}
