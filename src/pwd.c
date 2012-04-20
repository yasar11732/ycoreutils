#include <unistd.h> // getcwd
#include <stdlib.h>
#include <stdio.h>
#include <limits.h> // PATH_MAX
#include "utilities.h"

#define BUFFER_SIZE PATH_MAX
int main(int argc, char *argv[])
{
	char *dir = malloc(sizeof(char) * BUFFER_SIZE);
	if (getcwd(dir,BUFFER_SIZE) == NULL)
		exit_with_error(argv[0],"");
	puts(dir);
	return 0;
}
