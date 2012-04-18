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
STATIC_LIB_NAME      = lib$(LIB_BASE_NAME).a
SHARED_LIB_NAME      = lib$(LIB_BASE_NAME).so
STATIC_LIBRARY       = lib/$(STATIC_LIB_NAME)
SHARED_LIBRARY       = lib/$(SHARED_LIB_NAME)
LIBRARY_SRCS  = $(sort $(wildcard lib/*.c))
LIBRARY_OBJS  = $(LIBRARY_SRCS:.c=.o)

BINARY_SRCS  = $(sort $(wildcard src/*.c))
BINARY_NAMES = $(BINARY_SRCS:src/%.c=%)
BINARIES     = $(BINARY_NAMES:%=bin/%)

INCLUDES     = $(sort $(wildcard include/*.h))

CC      = musl-gcc
CFLAGS  = -std=c99 -D_XOPEN_SOURCE=700 -pipe
LDFLAGS = -static -l$(LIB_BASE_NAME)
INC     = -I./include
LIB     = -Llib
AR      = ar
RANLIB  = ranlib

-include config.mak

all: $(SHARED_LIBRARY) $(STATIC_LIBRARY) $(BINARIES)

install : $(DESTDIR)$(libdir)/$(LIB_NAME) $(INCLUDES:include/%=$(DESTDIR)$(includedir)/%) $(BINARY_NAMES:%=$(DESTDIR)$(bindir)/%)

clean:
	rm -fv $(LIBRARY)
	rm -fv $(LIBRARY_OBJS)
	rm -fv $(BINARIES)
	rm -fv *~
	rm -fv */*~
	rm -fv */*.swp
	rm -fv */.*.swp

strip: $(BINARIES)
	strip $^

$(STATIC_LIBRARY): $(LIBRARY_OBJS) $(INCLUDES)
	rm -f $@
	$(AR) rc $@ $(LIBRARY_OBJS)
	$(RANLIB) $@

$(SHARED_LIBRARY): $(LIBRARY_OBJS) $(INCLUDES)
	ld -shared $(LIBRARY_OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

bin/%: src/%.c $(LIBRARY)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $< $(LDFLAGS)

$(DESTDIR)$(libdir)/$(LIB_NAME): $(LIBRARY)
	install -D -m 644 $< $@

$(DESTDIR)$(includedir)/%: include/%
	install -D -m 644 $< $@

$(DESTDIR)$(bindir)/%: bin/%
	install -D -m 755 $< $@

test: tests/test.c $(LIBRARY)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $< $(LDFLAGS)
