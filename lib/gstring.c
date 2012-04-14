#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "gstring.h"

Gstring *gstrcat(const Gstring * const str1,const Gstring * const str2) {

    size_t s1len = str1->length;
    size_t s2len = str2->length;
    size_t total = s1len + s2len;

    char *buffer = malloc(sizeof(char) * (total + 1));
    char *temp = buffer;
    char *content = str1->content;

    while(s1len--)
        *temp++ = *content++;

    content = str2->content;
    while(s2len--)
        *temp++ = *content++;

    *temp = '\0';
    Gstring *newstring = malloc(sizeof(Gstring));
    newstring->content = buffer;
    newstring->length = total;
    return newstring;
}

Gstring *from_string(const char * const str) {
    Gstring *newstring = malloc(sizeof(Gstring));
    size_t size = strlen(str);
    newstring->length = size;
    char *buffer = malloc(sizeof(char) * (size + 1));
    newstring->content = strncpy(buffer,str,size + 1);
    return newstring;
}

char *to_string(Gstring *source) {
    char *newstr = malloc(sizeof(char) * (source->length + 1));
    return memcpy(newstr,
            source->content, 
            sizeof(char) * (source->length + 1));
}

void freegstring(Gstring *source) {
    free (source->content);
    free (source);
}
