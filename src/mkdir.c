#include <stdlib.h>
#include <sys/stat.h> // mkdir
#include <stdio.h> // perror
#include <string.h> // strtol
#include <unistd.h> // getopt
#include <errno.h> // errno :)
#include "utilities.h" // strtoken

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

        /*
         * Wow, hardcore suckage here...
         */

        if (parent) {
            char *rest = NULL;
            char *path_so_far = strtoken(argv[i],"/",&rest);
            if (*path_so_far == '\0') {
                // path starts with "/"
                free(path_so_far);
                path_so_far = "/";
            }

            while(*rest != '\0') {
                char *next_part;
                if (file_exists(path_so_far) == -1) {
                    if (mkdir(path_so_far, mode) == -1) {
                        fprintf(stderr, "%s: %s: %s",
                                argv[0], strerror(errno), argv[i]);
                        exit(EXIT_FAILURE);
                    }
                }
                next_part = strtoken(rest,"/",&rest);
                int size = strlen(path_so_far) + strlen(next_part) + 2;
                char *buffer = malloc(sizeof(char) * size);
                *buffer = '\0';
                strcat(buffer,path_so_far);
                strcat(buffer,"/");
                strcat(buffer,next_part);
                free (next_part);
                free (path_so_far);
                path_so_far = buffer;
            }
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
