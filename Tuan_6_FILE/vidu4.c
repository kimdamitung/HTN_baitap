#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp;
 	char c[] = "Example for function fread and fwrite";
 	char buffer[100];
	fp = fopen("file.txt", "w+");
	fwrite(c, strlen(c) + 1, 1, fp);
	fseek(fp, SEEK_SET, 0);
	fread(buffer, strlen(c)+1, 1, fp);
	printf("%s\n", buffer);
 	fclose(fp);
 	return(0);
}