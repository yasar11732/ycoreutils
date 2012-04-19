#include <stdlib.h>
#include <unistd.h> // getopt
#include <stdio.h>
#include <string.h>
#include "utilities.h"
int main(int argc, char *argv[])
{
	int newlineflag = 1;
	int escapeflag = 0;
	int option;
	int i;

	while ((option = getopt(argc, argv, "neE")) != -1)
		switch (option) {
		case 'n':
			newlineflag = 0;
			break;
		case 'e':
			escapeflag = 1;
			break;
		case 'E':
			escapeflag = 0;
			break;
		case '?':
			exit(EXIT_FAILURE);
		default:
			abort (); // this shouldn't happen!
		}
	
	for (i = optind; i < argc; ++i) {
		/* Don't put space before first argument! */
		if (i != optind)
			fwrite(" ",1,1,stdout);
		if (escapeflag)
			translate_escapes(argv[i]);
		printf(argv[i]);
	}

	if (newlineflag)
		fwrite("\n",1,1,stdout);
	return 0;
}
