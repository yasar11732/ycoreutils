#include <stdlib.h> // free
#include <stdio.h> // FILE, printf etc.
#include <sys/types.h> // uid_t
#include <unistd.h> // getuid
#include "utilities.h"

int
main()
{
    FILE *passwd;
    char *line = NULL;
    size_t line_size;

    passwd = fopen("/etc/passwd","r");

    uid_t uid = getuid();
    while (getline(&line, &line_size,passwd) != -1) {
        char *rest;
        char *name = strtoken(line,":",&rest);
        rest = strfind(rest, ":"); // discard password
        ++rest;
        char *user_id = strtoken(rest,":",&rest);
        if (str2int(user_id) == uid) {
            printf("%s\n",name);
            free (name);
            free (user_id);
            break;
        }
        free (name);
        free (user_id);
    }

    free (line);
    fclose(passwd);
    return 0;
}
