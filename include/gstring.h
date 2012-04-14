#ifndef _GSTRING_H_
#define _GSTRING_H_
typedef struct {
    char *content;
    size_t length; // excluding '\0'
} Gstring;

Gstring *gstrcat(const Gstring * const,const Gstring * const);
Gstring *from_string(const char * const);
char *to_string(Gstring *);
void freegstring(Gstring *);
#endif
