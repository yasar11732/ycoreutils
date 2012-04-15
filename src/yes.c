#include <stdio.h>

int main(int argc,char *argv[])
{
	if (argc > 1)
		for(;;) {
			int i;
			for(i = 1; i < argc - 1; ++i)
				printf("%s ",argv[i]);
			printf("%s\n",argv[argc-1]);
		}
	else
		for(;;)
			fwrite("y\n",sizeof(char),2,stdout);
	return 0;
}
