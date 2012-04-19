#include <stdio.h>
#include "utilities.h"

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 512
#endif

int cp(FILE *source, FILE *destination)
{
	char buffer[BLOCK_SIZE];
	for(;;) {
		size_t bytes = fread(buffer,  sizeof(char),BLOCK_SIZE,source);
		if (bytes > 0) {
			fwrite(buffer, sizeof(char), bytes, destination);
		}
		else {
			if (ferror(source) || ferror(destination))
				return -1;
			else
				return 0;
		}

	}
}
