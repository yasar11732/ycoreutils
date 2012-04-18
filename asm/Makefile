SOURCES = $(wildcard *.s)
OBJECTS = $(SOURCES:%.s=%.o)
BINS = $(SOURCES:%.s=%)
LD  = ld
AS  = as
CC  = gcc
CFLAGS = -static -nostdlib
ASFLAGS = --gstabs

all: $(BINS)
%: %.s
%: %.o lib/libsyscalls.a
	ld  $< ./lib/libsyscalls.a -o $@
strip: $(BINS)
	strip $^
clean:
	rm -f $(OBJECTS)
	rm -f $(BINS)
.PRECIOUS: $(OBJECTS)
