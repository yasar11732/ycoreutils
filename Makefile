#
# Makefile for ycoreutils
#
# Use config.mak to override any of the following variables.
# Do not make changes here.
#

prefix = /
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin

includedir = $(prefix)/include
libdir = $(prefix)/lib
syslibdir = /lib

LIB_BASE_NAME = ycoreutils
LIB_NAME      = lib$(LIB_BASE_NAME).a
LIBRARY       = lib/$(LIB_NAME)
LIBRARY_SRCS  = $(sort $(wildcard lib/*.c))
LIBRARY_OBJS  = $(LIBRARY_SRCS:.c=.o)

BINARY_SRCS  = $(sort $(wildcard src/*.c))
BINARIES     = $(BINARY_SRCS:src/%.c=%)

INCLUDES     = $(sort $(wildcard include/*.h))

CC      = musl-gcc
CFLAGS  = -std=c99 -D_XOPEN_SOURCE=700 -pipe
LDFLAGS = -static -l$(LIB_BASE_NAME)
INC     = -I./include
LIB     = -Llib
AR      = ar
RANLIB  = ranlib

-include config.mak

all: $(LIBRARY) $(BINARIES)

install : $(DESTDIR)$(libdir)/$(LIB_NAME) $(INCLUDES:include/%=$(DESTDIR)$(includedir)/%) $(BINARIES:%=$(DESTDIR)$(bindir)/%)

clean:
	rm -f $(LIBRARY)
	rm -f $(LIBRARY_OBJS)
	rm -f $(BINARIES)

strip: $(BINARIES)
	strip $(BINARIES)

$(LIBRARY): $(LIBRARY_OBJS) $(INCLUDES)
	rm -f $@
	$(AR) rc $@ $^
	$(RANLIB) $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

%: src/%.c $(LIBRARY)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $< $(LDFLAGS)

$(DESTDIR)$(libdir)/$(LIB_NAME): $(LIBRARY)
	install -D -m 644 $< $@

$(DESTDIR)$(includedir)/%: include/%
	install -D -m 644 $< $@

$(DESTDIR)$(bindir)/%: %
	install -D -m 755 $< $@

test: tests/test.c $(LIBRARY)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $< $(LDFLAGS)
