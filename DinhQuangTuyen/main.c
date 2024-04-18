#include <stdio.h>
#include <conio.h>
#include "osFile/osFile.h"

int main(){
	/* code */
	FILE *pFile = NULL;
	char ch;
	printf("Thao tac nut nhan di thang loz\n");
	while(1){
		if(_kbhit()){
			ch = _getch();
			/*bai cua thang quang gui*/
			if(ch == '1'){
				const char *text = "bbbbbbbbbb";
				add_char_in_file(pFile, "quang.txt", text);
			}else if(ch == '2'){
				display_file(pFile, "quang.txt");
			}else if(ch == '3'){
				const char *text = "chao cac ban";
				add_char_end_line(pFile, "quang.txt", text);
			}
			/*bai cua thang an gui*/
			if(ch == '4'){
				const char *text = "aaaaaaaaaa";
				add_char_in_file(pFile, "an.txt", text);
			}else if(ch == '5'){
				display_file(pFile, "an.txt");
			}else if(ch == '6'){
				const char *text = "chao cac ban";
				add_char_in_file(pFile, "an.txt", text);
			}
		}
	}
	return 0;
}