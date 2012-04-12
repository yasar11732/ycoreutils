#ifndef _UTILITIES_H__
#define _UTILITIES_H__
#include <stdio.h>
char *
strtoken(char * const, const char * const,char **);

char *
strfind(char * const string,const char * const chr);

int str2int(const char * const str);

int cp(FILE *, FILE *);
#endif
