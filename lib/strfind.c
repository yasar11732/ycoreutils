#include "utilities.h"
/*
 * Search string for a char, and return it's position.
 * if chr is not in string return NULL
 */

char *strfind(char * const string,const char * const chr)
{
	int i = 0;
	while (string[i] != '\0') {
		if (string[i] == *chr)
			return &(string[i]);
		++i;
	}
	return NULL;
}
