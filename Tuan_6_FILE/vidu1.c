#include <stdio.h>

int main(int argc, char const *argv[])
{
	/* code */
	FILE *pFile;
	int c;
	int n = 0;
	pFile = fopen("myfile.txt", "r");
	if(pFile == NULL)
		perror("Error openning file");
	else{
		do{
			c = fgetc(pFile);
			if(c == '$')
				n++;
		}while(c != EOF);
		fclose(pFile);
		printf("The file contains %d dollar sign characters ($).\n", n);
	}
	return 0;
}