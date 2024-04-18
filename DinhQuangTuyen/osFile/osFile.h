#ifndef OSFILE
#define OSFILE

#include <stdio.h>

void display_file(FILE *pFile, const char *filename);
void add_char_in_file(FILE *pFile, const char *filename, const char *text);
void add_char_end_line(FILE *pFile, const char *filename, const char *text);

#endif