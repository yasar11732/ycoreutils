#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include "utilities.h"

/* Scan a string for a octal value. If second argument is a positive
 * number, maximum of that many digits will be read. if consumed is not
 * null, actual number of characters read will be stored there.*/
int scan_octal(char *input, int maxdigits, int *consumed)
{
	int i = 0;
	int acc = 0; // accumulator
	if (maxdigits) {
		while(maxdigits--) {
			if(input[i] > '7' || input[i] < '0')
				break;
			acc = (8 * acc) + (input[i] - '0');
			++i;
		}
	} else {
		for(;;) {
			if(input[i] > '7' || input[i] < '0')
				break;
			acc = (8 * acc) + (input[i] - '0');
			++i;
		}
	}
	if(consumed != NULL)
		*consumed = i;
	return acc;
}

/* Scan a string for a hex value. If second argument is a positive
 * number, maximum of that many digits will be read. if consumed is not
 * null, actual number of characters read will be stored there.*/
int scan_hex(char *input, int maxdigits, int *consumed)
{
	int i = 0;
	int acc = 0; // accumulator
	if (maxdigits) {
		while(maxdigits--) {
			if (input[i] >= '0' && input[i] <= '9')
				acc = (16 * acc) + (input[i] - '0');
			else if (input[i] >= 'A' && input[i] <= 'F')
				acc = (16 * acc) + (input[i] - 'A' + 10);
			else if (input[i] >= 'a' && input[i] <= 'f')
				acc = (16 * acc) + (input[i] - 'a' + 10);
			else
				break;
			++i;
		}
	} else {
		for(;;) {
			if (input[i] >= '0' && input[i] <= '9')
				acc = (16 * acc) + (input[i] - '0');
			else if (input[i] >= 'A' && input[i] <= 'F')
				acc = (16 * acc) + (input[i] - 'A' + 10);
			else if (input[i] >= 'a' && input[i] <= 'f')
				acc = (16 * acc) + (input[i] - 'a' + 10);
			else
				break;
			++i;
		}
	}
	if(consumed != NULL)
		*consumed = i;
	return acc;
}

/* Turns backslash escapes into their corresponding values */
void translate_escapes(char * const string)
{
	size_t inputlength = strlen(string);
	char *temps = malloc((inputlength + 1) * sizeof(char));
	if (temps == NULL)
		exit(EXIT_FAILURE);
	size_t temps_i; // location on the temp string
	size_t s_i; // location on the actual string
	for (s_i = 0, temps_i = 0; s_i <= inputlength; ++s_i, ++temps_i)
		if (string[s_i] == '\\')
			switch(string[s_i + 1]) {
			case '\\':
				temps[temps_i] = '\\';
				++s_i;
				break;
			case 'a':
				temps[temps_i] = '\a';
				++s_i;
				break;
			case 'b':
				temps[temps_i] = '\b';
				++s_i;
				break;
			case 'c':
				goto finish_translate;
			case 'e':
				temps[temps_i] = 0x1b; // escape character
				++s_i;
				break;

			case 'f':
				temps[temps_i] = '\f';
				++s_i;
				break;
			case 'n':
				temps[temps_i] = '\n';
				++s_i;
				break;
			case 'r':
				temps[temps_i] = '\r';
				++s_i;
				break;
			case 't':
				temps[temps_i] = '\t';
				++s_i;
				break;
			case 'v':
				temps[temps_i] = '\v';
				++s_i;
				break;
			case '0': /* Octal value*/
				{
					int num_chars_consumed = 0;
					int value = scan_octal(string + s_i + 2, 3,&num_chars_consumed);
					if(num_chars_consumed) {
						temps[temps_i] = (char)value;
						s_i = s_i + num_chars_consumed + 1;
					} else {
						goto d;
					}
				}
				break;
			case 'x': /* Hex value*/
				{
					int num_chars_consumed = 0;
					int value = scan_hex(string + s_i + 2, 2,&num_chars_consumed);
					if(num_chars_consumed) {
						temps[temps_i] = (char)value;
						s_i = s_i + num_chars_consumed + 1;
					} else {
						goto d;
					}
				}
				break;
			d:
			default:
				temps[temps_i] = string[s_i];
				break;
			}

		else
			temps[temps_i] = string[s_i];
finish_translate:
	temps[++temps_i] = '\n';
	memcpy(string,temps,temps_i * sizeof(char));
}
