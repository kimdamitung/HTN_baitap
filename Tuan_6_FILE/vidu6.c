#include <stdio.h>

int main(int argc, char const *argv[])
{
	/* code */
	FILE *pFile;
	pFile = fopen("myfile.txt", "wb");
	fputs("this is an apple", pFile);
	fseek(pFile, 9, SEEK_SET);
	fputs("sam", pFile);
	fclose(pFile);
	return 0;
}