#include <stdlib.h>
#include <string.h>
#include "utilities.h"

/*
 * My version of strtok with some differences, because everyone knows
 * that strtok sucks;
 * If no delimeteter found in input, return a copy of input (this is
 * important, because caller will assume new string is returned), and
 * set *rest to end of input. Otherwise, return new string
 * up until the delimeter and set *rest to first position after the
 * delimeter in input.
 */

char * strtoken(char * const input, const char * const delim,char **rest) {
	char *delimpos = strfind(input, delim);

	if (delimpos == NULL) {
		// no delimeter in input
		size_t inputlength = strlen(input);
		char *result = malloc(sizeof(char) * (inputlength + 1));
		strcpy(result,input);
		*rest = &(input[inputlength]);
		return result;
	}
	int length = delimpos - input;
	char *result = malloc(sizeof(char) * (length + 1));
	memcpy(result, input, length);
	result[length] = '\0';
	*rest = delimpos + 1;
	return result;
}
