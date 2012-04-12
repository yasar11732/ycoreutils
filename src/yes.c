#include <stdio.h>

int main(int argc,char *argv[])
{
    char *str;
    if (argc == 2)
        str = argv[1];
    else
        str = "y";

    while (1)
        printf("%s\n",str);
    return 0;
}
