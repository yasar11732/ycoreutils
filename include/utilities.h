#ifndef _UTILITIES_H__
#define _UTILITIES_H__
#include <stdio.h> // FILE pointer.
char *strtoken(char * const, const char * const,char **);

char *strfind(char * const,const char * const);

int str2int(const char * const);

int cp(FILE *, FILE *);

int file_exists(const char * const);
#endif
