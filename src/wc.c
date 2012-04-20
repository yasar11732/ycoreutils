#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "utilities.h"
/* This programs purpose is to count characters, spaces or newlines.*/

size_t total_lines = 0;
size_t total_words = 0;
size_t total_chars = 0;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2048
#endif

#define PRINT_TOTALS (1 << 4)
#define D_SWITCH (1 << 3) // default: count all
#define C_SWITCH (1 << 2) // count chars
#define W_SWITCH (1 << 1) // count words
#define L_SWITCH (1 << 0) // count lines

int main(int argc,char *argv[])
{
	/* This is options.*/
	char flags = D_SWITCH;

	/* These are accumulators. */
	size_t chars = 0;
	size_t words = 0;
	size_t lines = 0;

	char buffer[BUFFER_SIZE];

	int i;

	/* This is to get command line options. */
	int option;

	while ((option=getopt(argc, argv,"clw")) != -1)
		switch (option) {
		case 'c':
			flags &= ~D_SWITCH;
			flags |= C_SWITCH;
			break;
		case 'w':
			flags &= ~D_SWITCH;
			flags |= W_SWITCH;
			break;
		case 'l':
			flags &= ~D_SWITCH;
			flags |= L_SWITCH;
			break;
		case '?':
			fprintf(stderr,"I don't support -%c option.\n",optopt);
			exit(EXIT_FAILURE);
		default:
			abort();
		}

	if (flags & D_SWITCH) // if default, enable all switches.
		flags |= (C_SWITCH | W_SWITCH | L_SWITCH);

	if (optind < argc -1)
		flags |= PRINT_TOTALS;

	/* Process command line arguments. */
	for (i = optind; i < argc; ++i) {
		FILE *inputstrm = fopen(argv[i], "r");

		if (inputstrm == NULL)
			exit_with_error(argv[0],argv[i]);
		size_t bytes;

		// initialize counters
		chars = 0;
		words = 0;
		lines = 0;
		int inword = 0;
		do {
			bytes = fread(buffer, sizeof(char), BUFFER_SIZE, inputstrm);
			if (!bytes)
				break;
			if (flags & C_SWITCH) { // count chars
				chars += bytes;
			}

			if (flags & W_SWITCH) { // count words
				int counter = bytes;
				while (counter--) {
					switch (buffer[counter]) {
					case '\n':
					case '\r':
					case '\f':
					case '\t':
					case ' ':
					case '\v':
						words += inword;
						inword = 0;
						break;
					default:
						inword = 1;
					}
				}
			}

			if (flags & L_SWITCH) { // count lines
				int counter = bytes;
				while (counter--)
					if (buffer[counter] == '\n')
						++lines;
			}
		} while (bytes == BUFFER_SIZE);

		words += inword;

		total_chars += chars;
		total_words += words;
		total_lines += lines;

		
		char *seperator = "";
		if (flags & L_SWITCH) {
			printf("%s%d",seperator,lines);
			seperator = "\t";
		}

		if (flags & W_SWITCH) {
			printf("%s%d",seperator,words);
			seperator = "\t";
		}
		
		if (flags & C_SWITCH)
			printf("%s%d",seperator,chars);
		
		printf(" %s\n",argv[i]);

	}

	if (flags & PRINT_TOTALS) {
		char *seperator = "";
		if (flags & L_SWITCH) {
			printf("%s%d",seperator, total_lines);
			seperator = "\t";
		}

		if (flags & W_SWITCH) {
			printf("%s%d",seperator,total_words);
			seperator = "\t";
		}
		
		if (flags & C_SWITCH)
			printf("%s%d",seperator,total_chars);
		
		puts(" Total\n");
	}

	return 0;
}
