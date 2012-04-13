#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "utilities.h"

int main(int argc, const char *argv[])
{
    if (argc != 3) {
        fprintf(stderr,"%s source target\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1],argv[2]) == 0) {
        fprintf(stderr,"source and target can't be same.\n");
        exit(EXIT_FAILURE);
    }

    FILE *src = fopen(argv[1],"r");
    if (src == NULL) {
        fprintf(stderr,"%s: %s: %s\n", argv[0], strerror(errno), argv[1] );
        exit(EXIT_FAILURE);
    }
    
    FILE *dst = fopen(argv[2],"w");
    if (dst == NULL) {
        fprintf(stderr,"%s: %s: %s\n", argv[0], strerror(errno), argv[1] );
        exit(EXIT_FAILURE);
    }

    if(cp(src,dst) == -1) {
        fprintf(stderr,"%s: %s\n", argv[0], strerror(errno));
        exit(EXIT_FAILURE);
    }
    return 0;
}
