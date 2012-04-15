#ifndef _GSTRING_H_
#define _GSTRING_H_

 /*
  * String and it's length.
  */
struct  Gstring {
	char *content;
	size_t length; // excluding '\0'
};

struct Gstring *gstrcat(const struct Gstring * const,
		const struct Gstring * const);

struct Gstring *togstring(const char * const);

char *fromgstring(struct Gstring *);

void freegstring(struct Gstring *);

struct Gstring *gstrdup(struct Gstring *);

struct Gstring *gstrtoken(struct Gstring * const,
		const char * const ,struct Gstring *);

int appendstr2gstring(struct Gstring *,char *);

int combinegstr(struct Gstring *, struct Gstring *);
#endif
