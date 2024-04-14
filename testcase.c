#include <stdio.h>
#include "osFILE/osFile.h"

int main(int argc, char const *argv[])
{
	/* code */
	FILE *pFile = NULL;
	display_file(pFile, "bai_4.txt");
	printf("==============================\n");
	// upper_first_text(pFile, "bai_4.txt");
	// printf("==============================\n");
	// display_file(pFile, "bai_4.txt");
	// printf("==============================\n");
	// lower_first_text(pFile, "bai_4.txt");
	// printf("==============================\n");
	// display_file(pFile, "bai_4.txt");
	printf("==============================\n");
	append_char_position(pFile, "bai_4.txt", 9, "duy ");
	display_file(pFile, "bai_4.txt");
	printf("==============================\n");
	return 0;
}