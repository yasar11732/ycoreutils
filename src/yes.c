#include <stdio.h>

int main(int argc,char *argv[])
{
    if (argc > 1)
        while (1) {
            int i;
            
            for(i = 1; i < argc - 1; ++i)
                printf("%s ",argv[i]);

            printf("%s\n",argv[argc-1]);
        }
    else
        while (1)
            printf("y\n");
    return 0;
}
