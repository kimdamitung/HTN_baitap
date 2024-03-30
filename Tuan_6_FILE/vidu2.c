#include <stdio.h>

int main(int argc, char const *argv[])
{
	/* code */
	FILE *pFile;
	char string[100];
	pFile = fopen("myfile.txt", "r");
	if(pFile == NULL)
		perror("Error openning file");
	else{
		if(fgets(string, 100, pFile) != NULL)
			puts(string);
		fclose(pFile);
	}
	return 0;
}