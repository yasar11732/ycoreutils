#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include "utilities.h"

int
str2int(const char * const str)
{
    int acc = 0;
    int i;
    for (i = 0; str[i] != '\0'; ++i)
        acc = (10 * acc) + (str[i] - 48); // 48 -> 0 in ascii
    return acc;
}

/*
 * Search string for a char, and return it's position.
 * if string is NULL, return NULL
 * if chr is not in string return NULL
 */

char *
strfind(char * const string,const char * const chr)
{
    int i = 0;
    if (string == NULL)
        return NULL;
    while (string[i] != '\0') {
        if (string[i] == *chr)
            return &(string[i]);
        ++i;
    }
    return NULL;
}

char *
strtoken(char * const input, const char * const delim,char **rest) {
    char *delimpos = strfind(input, delim);

    if (delimpos == NULL) {
        // no delimeter in input
        *rest = NULL;
        return input;
    }
    int length = delimpos - input;
    char *result = malloc(sizeof(char) * (length + 1));
    memcpy(result, input, length);
    result[length] = '\0';
    *rest = delimpos + 1;
    return result;
}
