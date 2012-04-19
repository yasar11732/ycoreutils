#include "utilities.h"

/*
 * Like str2int, only good for positive numbers
 * Note: This function is for internal use in
 * library.
 */
int str2int_p(const char * const str)
{
	int acc = 0;
	int i;
	for (i = 0; str[i] != '\0'; ++i) {
		if (str[i] > '9' || str[i] < '0')
			break; // not a number
		acc = (10 * acc) + (str[i] - '0');
	}
	return acc;
}

/*
 * Kind of a atoi clone. Making my own functions makes
 * me happier, since I know for sure how my functions
 * are implemented. It makes me confident!
 */
int str2int(const char * const str)
{
	if (*str == '-')
		return -1 * str2int_p(str + 1);
	return str2int_p(str);
}
