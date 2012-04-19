#ifndef _UTILITIES_H__
#define _UTILITIES_H__
#include <stdio.h> // FILE pointer.
void translate_escapes(char * const);

char *strtoken(char * const, const char * const,char **);

char *strfind(char * const,const char * const);

int str2int(const char * const);

int cp(FILE *, FILE *);

int file_exists(const char * const);

void exit_with_error(const char const *programname, const char const *componentname);
#endif
