AR = ar
RANLIB = ranlib
SOURCES = $(wildcard *.s)
OBJECTS = $(SOURCES:%.s=%.o)

ASFLAGS = --gstabs

all: libsyscalls.a libsyscalls.so

libsyscalls.a: $(OBJECTS)
	rm -f $@
	$(AR) rc $@ $^
	$(RANLIB) $@

libsyscalls.so: $(OBJECTS)
	ld -shared $^ -o $@

.PRECIOUS: $(OBJECTS)
