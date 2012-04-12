#include "utilities.h"

int test_str2int()
{
   char *num1 = "10";
   char *num2 = "0";
   char *num3 = "-523";
   char *num4 = "";
   char *num5 = "asd";
   if (str2int(num1) != 10)
       return -1;
   if (str2int(num2) != 0)
       return -1;
   if (str2int(num3) != -523)
       return -1;
   if (str2int(num4) != 0)
       return -1;
   if (str2int(num5) != 0)
       return -1;
   return 0;
}

int main()
{
    printf("Testing str2int...");
    if (test_str2int() == 0)
        printf("OK.\n");
    else
        printf("FAIL.\n");
    return 0;
}
