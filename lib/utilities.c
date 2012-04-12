#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include "utilities.h"


/*
 * Like str2int, only good for positive numbers
 * Note: This function is for internal use in
 * library.
 */
int
str2int_p(const char * const str)
{
    int acc = 0;
    int i;
    for (i = 0; str[i] != '\0'; ++i) {
        if (str[i] > 57 || str[i] < 48)
            break; // not a number
        acc = (10 * acc) + (str[i] - 48); // 48 -> 0 in ascii
    }
    return acc;
}
/*
 * Kind of a atoi clone. Making my own functions makes
 * me happier, since I know for sure how my functions
 * are implemented. It makes me confident!
 */

int
str2int(const char * const str)
{
    if (*str == 45) { // 45 -> ascii value of "-"
        return -1 * str2int_p(str + 1);
    }
    return str2int_p(str);
}

/*
 * Search string for a char, and return it's position.
 * if chr is not in string return NULL
 */

char *
strfind(char * const string,const char * const chr)
{
    int i = 0;
    while (string[i] != '\0') {
        if (string[i] == *chr)
            return &(string[i]);
        ++i;
    }
    return NULL;
}

/*
 * My version of strtok with some differences, because everyone knows
 * that strtok sucks;
 * If no delimeteter found in input, return a copy of input (this is
 * important, because caller will assume new string is returned), and
 * set *rest to end of input. Otherwise, return new string
 * up until the delimeter and set *rest to first position after the 
 * delimeter in input.
 */

char *
strtoken(char * const input, const char * const delim,char **rest) {
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
