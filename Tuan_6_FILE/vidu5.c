#include <stdio.h>

int main(int argc, char const *argv[])
{
	/* code */
	FILE *pFile;
	char sentence[256];
	printf("Enter sentence to append: ");
	fgets(sentence, 256, stdin);
	pFile = fopen("myfile.txt", "a");
	fputs(sentence, pFile);
	fclose(pFile);
	return 0;
}