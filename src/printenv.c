#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc,char *argv[], char *envp[])
{
	if (argc == 1) {
		while (*envp)
			puts(*envp++);
		return 0;
	}
	int zeroflag = 0;
	int option;
	int i;

	while ((option = getopt(argc,argv,"0")) != -1)
		switch (option) {
		case '0':
			zeroflag = 1;
			break;
		case '?':
			fprintf(stderr, "I don't support -%c option.\n",optopt);
			exit(EXIT_FAILURE);
			break;
		default:
			abort();
		}
	if (argc <= optind) {
		// no spesific arguments, just print all.
		if (zeroflag)
			while (*envp) {
				/* +1 for null byte */
				fwrite(*envp, sizeof(char), strlen(*envp) + 1, stdout);
				++envp;
			}
		else
			while (*envp)
				puts(*envp++);
	} else {
		if (zeroflag) {
			for (i = optind; i < argc; ++i) {
				char *value = getenv(argv[i]);
				fwrite(value, sizeof(char), strlen(value) + 1, stdout);
			}
		} else {
			for (i = optind; i < argc; ++i) {
				char *value = getenv(argv[i]);
				puts(value);
			}
		}
	}
}
