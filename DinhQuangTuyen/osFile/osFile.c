#include "osFile.h"

void display_file(FILE *pFile, const char *filename){
	char string[256];
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Error open file\n");
	while(fgets(string, 256, pFile) != NULL)
		printf("%s", string);
	printf("\n");
	fclose(pFile);
}

void add_char_in_file(FILE *pFile, const char *filename, const char *text){
	pFile = fopen(filename, "w");
	if(pFile != NULL)
		fprintf(pFile, "%s ", text);
	fclose(pFile);
}

void add_char_end_line(FILE *pFile, const char *filename, const char *text){
	pFile = fopen(filename, "a");
	if(pFile != NULL)
		fprintf(pFile, "%s\n", text);
	fclose(pFile);
}

