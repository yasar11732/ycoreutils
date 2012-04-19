#include <stdlib.h>
#include <sys/stat.h> // mkdir
#include <stdio.h> // perror
#include <string.h> // strtol
#include <unistd.h> // getopt
#include <errno.h> // errno :)
#include "gstring.h" // gstring thingies.
#include "utilities.h"

void exit_with_error(const char const *programname, const char const *componentname) {
	fprintf(stderr, "%s: %s: %s\n", programname, strerror(errno), componentname);
	exit(errno);
}

int main(int argc, char *argv[])
{
	mode_t mask = umask(0);
	mode_t mode = 0777&~mask;

	int verboseflag = 0;
	int parentflag = 0;
	int option;
	int i;

	while ((option = getopt(argc, argv, "pvm:")) != -1)
		switch (option) {
		case 'm':
			mode = strtol(optarg,NULL,8);
			break;
		case 'p':
			parentflag = 1;
			break;
		case 'v':
			verboseflag = 1;
			break;
		case '?':
			exit(EXIT_FAILURE);
		default:
			abort (); // this shouldn't happen!
		}
	
	// Handle other command line arguments
	for (i = optind; i < argc; ++i) {
		errno = 0;
		if (parentflag) {
			/* Important: Don't delete *gargv until while loop
			 * finishes, rest's content is just pointer to it's
			 * content. */
			struct Gstring rest;
			struct Gstring *gargv = togstring(argv[i]);
			struct Gstring *path_so_far = gstrtoken(gargv,"/",&rest);

			while(rest.length > 0) {
				struct Gstring *next_part;

				if(mkdir(path_so_far->content, mode) == -1 && errno != EEXIST)
					exit_with_error(argv[0], argv[i]);

				next_part = gstrtoken(&rest,"/",&rest);
				appendstr2gstring(path_so_far,"/");
				combinegstr(path_so_far,next_part);
			}
			freegstring (gargv);
			freegstring (path_so_far);
		}

		if (mkdir(argv[i],mode) == -1)
			if (!parentflag || errno != EEXIST)
				exit_with_error(argv[0], argv[i]);

		if (verboseflag && errno != EEXIST)
			printf("%s created.\n",argv[i]);
	}
	return 0;
}
