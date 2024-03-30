#include <stdio.h>

void putext_interger_counter_buttons(FILE *pFile, const char *filename, int counter){
	pFile = fopen(filename, "w");
	if(pFile != NULL){
		fprintf(pFile, "%d", counter);
		fclose(pFile);
	}
}

void display_counter_buttons(FILE *pFile, const char * filename){
	char string[10];
	pFile = fopen(filename, "r");
	if(pFile == NULL)
		perror("error open file");
	else{
		if(fgets(string, 10, pFile) != NULL)
			puts(string);
		fclose(pFile);
	}
}

void counter_text(FILE *pFile, const char *filename){
	int c;
	int n = 0;
	pFile = fopen (filename,"r");
	FILE *tempFile;
	tempFile = fopen("temp.txt", "w");
	if(pFile == NULL || tempFile == NULL)
		perror("Error open file!!!!!");
	else{
 		do{
			c = fgetc(pFile);
			if (c == 'a'){
				n++;
				fputc('A', tempFile);
			}else{
				fputc(c, tempFile);
			}
		} while (c != EOF);
 	}
 	printf ("So chu a xuat hien: %d\n",n);
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

int main(int argc, char const *argv[])
{
	/* code */
	FILE *pFile;
	int c = 1;
	counter_text(pFile, "text.txt");
	return 0;
}