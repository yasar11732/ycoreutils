#include <sys/stat.h>
#include "utilities.h"
// return 0 if file exists, -1 if not
int file_exists(const char * const path)
{
	struct stat buff;
	if (lstat(path,&buff) == 0)
		return 0;
	return -1;
}
