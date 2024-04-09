#include <stdio.h>
#include <conio.h>
#include "osFILE/osFile.h"

int main(int argc, char const *argv[])
{
	/* code */
	FILE *pFile = NULL;
	char ch;
	int counter = 0;
	printf("Thao tac nut nhan di thang loz\n");
	while(1){
		if(_kbhit()){
			ch = _getch();
			/*begin code 1*/
			if(ch == '1')
				counter++;
			else if(ch == '2')
				display_file(pFile, "bai_1.txt");
			else if(ch == '3')
				counter = 0;
			add_number_in_file(pFile, "bai_1.txt", counter);
			/*end code 1*/
			/*begin code 2*/
			if(ch == '4')
				printf("So a: %d\n", counter_text(pFile, "bai_2.txt"));
			else if(ch == '5')
				convert_a_to_A(pFile, "bai_2.txt");
			else if(ch == '6')
				add_number_end_line(pFile, "bai_2.txt", counter_text(pFile, "bai_2.txt"));
			else if(ch == '7')
				display_file(pFile, "bai_2.txt");
			/*end code 2*/
			/*begin code 3*/
			if(ch == '8')
				printf("So number: %d\n", check_number_in_file(pFile, "bai_3.txt"));
			else if(ch == '9')
				remove_number_in_file(pFile, "bai_3.txt");
			else if(ch == '0')
				add_number_end_line(pFile, "bai_3.txt", sum_number_lower(pFile, "bai_3.txt"));
			else if(ch == 'a')
				display_file(pFile, "bai_3.txt");
			/*end code 3*/
			/*begin code 4*/
			if(ch == 'b')
				printf("So ki tu thuong: %d\n", check_text_lower_in_file(pFile, "bai_4.txt"));
			else if(ch == 'c')
				convert_lower_to_upper(pFile, "bai_4.txt");
			else if(ch == 'd'){
				remove_number_in_file(pFile, "bai_4.txt");
				char text[256] = "The end";
				add_char_end_line(pFile, "bai_4.txt", text);
			}else if(ch == 'e')
				display_file(pFile, "bai_4.txt");
			/*end code 4*/
		}
	}
	return 0;
}