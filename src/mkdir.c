#include <stdlib.h>
#include <sys/stat.h> // mkdir
#include <stdio.h> // perror
#include <string.h> // strtol
#include <unistd.h> // getopt
#include <errno.h> // errno :)
#include "gstring.h" // also includes utilities

// return 0 if file exists, -1 if not
int file_exists(const char * const path)
{
    struct stat buff;
    if (lstat(path,&buff) == 0)
        return 0;
    return -1;
}

/*
 * This function sucks, but it's the best I could
 * come up with
 */

int main(int argc, char *argv[])
{
    mode_t mask = umask(0);
    mode_t mode = 0777 & ~mask;

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

    for (i = optind; i < argc; ++ i) {

        if (parent) {
            Gstring rest;
            Gstring *gargv = to_gstring(argv[i]);
            Gstring *path_so_far = gstrtoken(gargv,"/",&rest);
            
            while(rest.length > 0) {
                Gstring *next_part;
                if (path_so_far->length > 0 && 
                        file_exists(path_so_far->content) == -1) {
                    if (mkdir(path_so_far->content, mode) == -1) {
                        fprintf(stderr, "%s: %s: %s",
                                argv[0], strerror(errno), argv[i]);
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
        if (verbose)
            printf("%s created.\n",argv[i]);
    }

    return 0;
}
