#ifndef _GSTRING_H_
#define _GSTRING_H_
typedef struct {
    char *content;
    size_t length; // excluding '\0'
} Gstring;

Gstring *gstrcat(const Gstring * const,const Gstring * const);
Gstring *to_gstring(const char * const);
char *from_gstring(Gstring *);
void freegstring(Gstring *);
Gstring *gstrdup(Gstring *);
Gstring *gstrtoken(Gstring * const, const char * const , Gstring *);
int appendstr2gstring(Gstring *,char *);
int combinegstr(Gstring *, Gstring *);
#endif
