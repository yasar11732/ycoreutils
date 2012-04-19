#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include "utilities.h"
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
				/* Not implemented */
			case 'x': /* Hex value*/
				/* Not implemented */
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
