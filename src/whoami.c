#include <stdlib.h> // exit, EXIT_FAILURE
#include <stdio.h> // printf etc.
#include <sys/types.h> // uid_t
#include <pwd.h> // getpwuid
#include <unistd.h> // getuid
#include <string.h>
#include <errno.h>
#include "utilities.h"

int
main(int argc, char *argv[])
{

    uid_t uid = getuid();
    struct passwd *pwd = getpwuid(uid);
    if (pwd == NULL) {
        fprintf(stderr,"%s: %s", argv[0], strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("%s\n",pwd->pw_name);
    return 0;
}
