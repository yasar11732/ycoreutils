#include <stdlib.h> // EXIT, EXIT_FAILURE
#include <string.h> // strcmp
#include <stdio.h> // FILE and stuff
#include <errno.h>
#include "utilities.h"

int
main(int argc, const char *argv[])
{
    if (argc == 1) { // copy stdin to stdout
        if (cp(stdin,stdout) == 0)
            return 0;
        else
            return 1;
    }
    else { // copy arguments to stdout
        int i;
        for (i = 1; i < argc; ++i) {
            FILE *f;
            switch (strcmp(argv[i],"-")) {
                case 0: // use stdin
                    if(cp(stdin,stdout) == -1) {
                        perror(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    break;
                default: // use file
                    f = fopen(argv[i],"r");
                    if (f == NULL) {
                        fprintf(stderr,"%s: %s: %s\n",
                                argv[0],
                                strerror(errno),
                                argv[i]);
                        exit(EXIT_FAILURE);
                    }
                    if (cp(f,stdout) == -1) {
                        fclose(f);
                        perror(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    fclose(f);
                    break;
            }
        }
    }
    return 0;
}
