#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int test_strfind()
{
    char *str1 = "yasar";
    char *str2 = "";
    char *str3 = "osman";

    char *ain1 = strfind(str1,"a");
    if (ain1 - str1 != 1)
        return -1;
    if (strfind(str2,"k") != NULL)
        return -1;
    if (strfind(str3,"k") != NULL)
        return -1;
    return 0;
}

int test_strtoken()
{
    char *str1 = "ya:sar";
    char *str2 = "arabaci";
    char *str3 = ":yasar";
    char *str4 = "arabaci:";

    char *rest;

    char *part1 = strtoken(str1,":",&rest);

    if (strcmp(part1,"ya") != 0)
        return -1;
    if (strcmp(rest,"sar") != 0)
        return -1;
    free (part1);

    char *part2 = strtoken(str2,":",&rest);
    if (part2 == str2)
        return -1;
    if (strcmp(part2,"arabaci") != 0)
        return -1;
    if (*rest != '\0')
        return -1;
    free (part2);

    char *part3 = strtoken(str3,":",&rest);
    if (*part3 != '\0')
        return -1;
    if (strcmp(rest,"yasar") != 0)
        return -1;
    free(part3);

    char *part4 = strtoken(str4,":",&rest);
    if(strcmp(part4,"arabaci") != 0)
        return -1;
    if (*rest != '\0')
        return -1;
    free (part4);
    return 0;
}

int main()
{
    printf("Testing str2int...");
    if (test_str2int() == 0)
        printf("OK.\n");
    else
        printf("FAIL.\n");
    
    printf("Testing strfind...");
    if (test_strfind() == 0)
        printf("OK.\n");
    else
        printf("FAIL.\n");
    
    printf("Testing strtoken...");
    if (test_strtoken() == 0)
        printf("OK.\n");
    else
        printf("FAIL.\n");
    return 0;
}
