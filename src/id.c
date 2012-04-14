#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc,char *argv[])
{
    int gflag = 0;
    int Gflag = 0;
    int nflag = 0;
    // int rflag = 0; // not-implemented yet.
    int uflag = 0;

    struct passwd *pwd;
    uid_t uid;
    int c;

    while ((c = getopt(argc, argv, "gGnru")) != -1)
        switch (c) {
        case 'g':
            if (Gflag || uflag) {
                fprintf(stderr,"You can only have one of -u -g and -G\n");
                exit(EXIT_FAILURE);
            }
            gflag = 1;
            break;
        case 'G':
            if (gflag || uflag) {
                fprintf(stderr,"You can only have one of -u -g and -G\n");
                exit(EXIT_FAILURE);
            }
            Gflag = 1;
            break;
        case 'n':
            nflag = 1;
            break;
        case 'r':
            // rflag = 1;
            break;
        case 'u':
            if (gflag || Gflag) {
                fprintf(stderr,"You can only have one of -u -g and -G\n");
                exit(EXIT_FAILURE);
            }
            uflag = 1;
            break;
        }

    if (optind >= argc) {
        // no spesific username given
        uid = getuid();
        pwd = getpwuid(uid);
    } else {
        pwd = getpwnam(argv[optind]);
    }

    if (pwd == NULL) {
        fprintf(stderr,"%s: %s", argv[0], strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (uflag) {
        if (nflag) {
            printf("%s\n",pwd->pw_name);
            return 0;
        }
        printf("%i\n",pwd->pw_uid);
        return 0;
    }

    if (gflag) {
        if (nflag) {
            struct group *g = getgrgid(pwd->pw_gid);
            printf("%s\n",g->gr_name);
            return 0;
        }
        printf("%i\n",pwd->pw_gid);
        return 0;
    }

    if(Gflag) {
        fprintf(stderr,"%s: This usage isn't implemented yet.\n",argv[0]);
        return 1;
    }

    // default to printing all information.
    return 0;
}
