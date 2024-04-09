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

/*bai 1*/
void add_number_in_file(FILE *pFile, const char *filename, int number){
	pFile = fopen(filename, "w");
	if(pFile != NULL)
		fprintf(pFile, "%d\n", number);
	fclose(pFile);
}
/*bai 2*/
int counter_text(FILE *pFile, const char *filename){
	int c, n = 0;
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Error open file\n");
	while((c = fgetc(pFile)) != EOF)
		if(c == 'a')
			n++;
	fclose(pFile);
	return n;
}

void convert_a_to_A(FILE *pFile, const char *filename){
	int c, n = 0;
	pFile = fopen(filename, "r");
	FILE *tempFile;
	tempFile = fopen("temp.txt", "w");
	if(pFile == NULL || tempFile == NULL)
		perror("Error open file");
	while((c = fgetc(pFile)) != EOF){
		if(c == 'a')
			fputc('A', tempFile);
		else
			fputc(c, tempFile);
	}
	fclose(pFile);
	fclose(tempFile);
	pFile = fopen(filename, "w");
	tempFile = fopen("temp.txt", "r");
	while((c = fgetc(tempFile)) != EOF)
		fputc(c, pFile);
	fclose(pFile);
	fclose(tempFile);
	remove("temp.txt");
}

void add_number_end_line(FILE *pFile, const char *filename, int number){
	pFile = fopen(filename, "a");
	if(pFile == NULL)
		perror("Error open file");
	fprintf(pFile, "%d", number);
	fclose(pFile);
}
/*bai 3*/
int check_number_in_file(FILE *pFile, const char *filename){
	int c, n = 0;
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Error open file");
	while((c = fgetc(pFile)) != EOF)
		if(c >= '0' && c <= '9')
			n++;
	fclose(pFile);
	return n;
}

void remove_number_in_file(FILE *pFile, const char *filename){
	pFile = fopen(filename, "r");
	FILE *tempFile = fopen("temp.txt", "w");
	if(pFile == NULL || tempFile == NULL)
		perror("Error open file");
	int c;
	while((c = fgetc(pFile)) != EOF)
		if(c < '0' || c > '9')
			fputc(c, tempFile);
	fclose(pFile);
	fclose(tempFile);
	pFile = fopen(filename, "w");
	tempFile = fopen("temp.txt", "r");
	while((c = fgetc(tempFile)) != EOF) 
		fputc(c, pFile);
	fclose(pFile);
	fclose(tempFile);
	remove("temp.txt");
}

int sum_number_lower(FILE *pFile, const char *filename){
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Error open file");
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
/*bai 4*/
int check_text_lower_in_file(FILE *pFile, const char *filename){
	int c;
	int n = 0;
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("Error open file!!!");
	while((c = fgetc(pFile)) != EOF){
		if(c >= 'a' && c <= 'z')
			n++;
	}
	return n;
}

void convert_lower_to_upper(FILE *pFile, const char *filename){
	int c;
	pFile = fopen (filename,"r");
	FILE *tempFile;
	tempFile = fopen("temp.txt", "w");
	if(pFile == NULL || tempFile == NULL)
		perror("Error open file!!!!!");
	while((c = fgetc(pFile)) != EOF){
		if(c >= 'a' && c <= 'z')
			fputc(c - 32, tempFile);
		else
			fputc(c, tempFile);
	}
 	fclose (pFile);
	fclose(tempFile);
	pFile = fopen(filename, "w");
	tempFile = fopen("temp.txt", "r");
	while((c = fgetc(tempFile)) != EOF){
		fputc(c, pFile);
	}
	fclose (pFile);
	fclose(tempFile);
	remove("temp.txt");
}

void add_char_end_line(FILE *pFile, const char *filename, char text[256]){
	pFile = fopen(filename, "a");
	if(pFile == NULL)
		perror("Error open file");
	fputs(text, pFile);
	fclose(pFile);
}