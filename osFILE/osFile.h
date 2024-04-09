#ifndef OSFILE
#define OSFILE

#include <stdio.h>

void display_file(FILE *pFile, const char *filename);
/*bai 1*/
void add_number_in_file(FILE *pFile, const char *filename, int number);
/*bai 2*/
int counter_text(FILE *pFile, const char *filename);
void convert_a_to_A(FILE *pFile, const char *filename);
void add_number_end_line(FILE *pFile, const char *filename, int number);
/*bai 3*/
int check_number_in_file(FILE *pFile, const char *filename);
void remove_number_in_file(FILE *pFile, const char *filename);
int sum_number_lower(FILE *pFile, const char *filename);
/*bai 4*/
int check_text_lower_in_file(FILE *pFile, const char *filename);
void convert_lower_to_upper(FILE *pFile, const char *filename);
void add_char_end_line(FILE *pFile, const char *filename, char text[256]);

#endif