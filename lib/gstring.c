#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "gstring.h"
#include "utilities.h"

Gstring *gstrcat(const Gstring * const str1,const Gstring * const str2)
{

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

Gstring *to_gstring(const char * const str)
{
    Gstring *newstring = malloc(sizeof(Gstring));
    size_t size = strlen(str);
    newstring->length = size;
    char *buffer = malloc(sizeof(char) * (size + 1));
    newstring->content = strncpy(buffer,str,size + 1);
    return newstring;
}

char *from_gstring(Gstring *source)
{
    char *newstr = malloc(sizeof(char) * (source->length + 1));
    return memcpy(newstr,
            source->content, 
            sizeof(char) * (source->length + 1));
}

void freegstring(Gstring *source)
{
    free (source->content);
    free (source);
}

int appendstr2gstring(Gstring *gstr,char *str)
{
    size_t len = strlen(str);
    char *newstr = realloc(gstr->content,
            sizeof(char) * (gstr->length + len + 1));

    if (newstr == NULL)
        return -1;
    
    memcpy(newstr + gstr->length, str, sizeof(char) * (len + 1));
    gstr->content = newstr;
    gstr->length += len;
    return 0;
}

/*
 * Adds second one into first one, and free's second one
 */

int combinegstr(Gstring *gstr1, Gstring *gstr2)
{
    char *newstr = realloc(gstr1->content,
            gstr1->length + gstr2->length + 1);
    if (newstr == NULL)
        return -1;
    memcpy(newstr + gstr1->length, gstr2->content, gstr2->length + 1);
    gstr1->content = newstr;
    gstr1->length += gstr2->length;
    freegstring(gstr2);
    return 0;
}

Gstring *gstrdup(Gstring *input)
{
    char *buffer = malloc(sizeof(char) * (input->length + 1));
    Gstring *newstring = malloc(sizeof(Gstring));
    newstring->content = memcpy(buffer, input->content, input->length + 1);
    newstring->length = input->length;
    return newstring;
}
/*
 * Like strtoken, but for gstrings.
 * Important rest's content is part of 
 * input's content. BE CAREFULL with that!
 */
Gstring *gstrtoken(Gstring * const input, const char * const delim, Gstring *rest)
{
    char *delimpos = strfind(input->content, delim);
    if (delimpos == NULL) {
        // no delimeter in input
        Gstring *newstring = gstrdup(input);
        rest->length  = 0;
        rest->content = &(input->content[input->length]);
        return newstring;
    }

    size_t new_length = delimpos - input->content;
    char *buffer = malloc(sizeof(char) * (new_length + 1));
    memcpy(buffer, input->content, new_length);
    buffer[new_length] = '\0';
    rest->content   = delimpos + 1;
    rest->length    = input->length - new_length - 1; 
    Gstring *newstring  = malloc(sizeof(Gstring));
    newstring->content = buffer;
    newstring->length  = new_length;
    return newstring;
}
