#include <stdlib.h>
#include <string.h> // strcmp
#include <unistd.h> // getopt
#include <stdio.h>
#include "utilities.h"
#define BUFFER_SIZE 512
int main(int argc,char *argv[])
{
	int appendflag = 0;
	int option;
	int i;
	int num_files;
	int num_bytes;
	char buffer[BUFFER_SIZE];
	while ((option = getopt(argc, argv,"a")) != -1)
		switch (option) {
		case 'a':
			appendflag = 1;
			break;
		case '?':
			fprintf(stderr,"We don't support -%c option.\n",optopt);
			exit(EXIT_FAILURE);
		default:
			abort();
		}
	num_files = argc - optind;
	FILE **outputfiles = malloc(num_files * sizeof(FILE *));
	for(i=optind; i < argc; ++i) {
		if (strcmp("-",argv[i]) == 0) {
			outputfiles[i - optind] = stdout;
			continue;
		}
		if (appendflag)
			outputfiles[i - optind] = fopen(argv[i],"a");
		else
			outputfiles[i - optind] = fopen(argv[i],"w");
		if (outputfiles[i - optind] == NULL)
			exit_with_error(argv[0],argv[i]);
	}

	while((num_bytes = fread(buffer, sizeof(char), BUFFER_SIZE, stdin)) > 0) {
		// print to stdout:
		fwrite(buffer, sizeof(char), num_bytes, stdout);
		for(i = 0; i < num_files; ++i) {
			if(fwrite(buffer, sizeof(char), num_bytes, outputfiles[i]) == -1)
				exit_with_error(argv[0],argv[i + optind]);
		}
	}
	return 0;
}
