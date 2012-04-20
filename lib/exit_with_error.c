#include <stdlib.h> // exit
#include <stdio.h> // fprintf
#include <string.h> // strerror
#include <errno.h>
void exit_with_error(const char const *programname, const char const *componentname)
{
	fprintf(stderr, "%s: %s: %s\n", programname, strerror(errno), componentname);
	exit(errno);
}
