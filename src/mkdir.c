#include <stdlib.h>
#include <sys/stat.h> // mkdir
#include <stdio.h> // perror
#include <string.h> // strtol
#include <unistd.h> // getopt
#include <errno.h> // errno :)
#include "gstring.h" // gstring thingies.
#include "utilities.h"

int main(int argc, char *argv[])
{
	mode_t mask = umask(0);
	mode_t mode = 0777&~mask;

	int verbose = 0;
	int parent  = 0;
	int c;
	int i;

	while ((c = getopt(argc, argv, "pvm:")) != -1)
		switch (c) {
		case 'm':
			mode = strtol(optarg,NULL,8);
			break;
		case 'p':
			parent = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		case '?':
			exit(EXIT_FAILURE);
		default:
			abort ();
		}
	// Handle other command line arguments
	for (i = optind; i < argc; ++i) {
		errno = 0;
		if (parent) {
			struct Gstring rest;
			struct Gstring *gargv = togstring(argv[i]);
			struct Gstring *path_so_far = gstrtoken(gargv,"/",&rest);

			while(rest.length > 0) {
				struct Gstring *next_part;
				if (path_so_far->length > 0 &&
						file_exists(path_so_far->content) == -1) {
					if (mkdir(path_so_far->content, mode) == -1) {
						fprintf(stderr, "%s: %s: %s",
								argv[0],
								strerror(errno),
								argv[i]);
						exit(EXIT_FAILURE);
					}
				}
				next_part = gstrtoken(&rest,"/",&rest);
				appendstr2gstring(path_so_far,"/");
				combinegstr(path_so_far,next_part);
			}
			freegstring (gargv);
			freegstring (path_so_far);
		}

		if (mkdir(argv[i],mode) == -1) {
			if (!parent || errno != EEXIST) {
				fprintf(stderr, "%s: %s: %s\n",
						argv[0],strerror(errno), argv[i]);
				exit(EXIT_FAILURE);
			}
		}
		if (verbose && errno != EEXIST)
			printf("%s created.\n",argv[i]);
	}
	return 0;
}
