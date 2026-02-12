# Generic Quicksort — build with gcc or clang, C99
CC ?= gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99
CPPFLAGS = -Iinclude
SRCDIR = src

SORT_OBJS = $(SRCDIR)/quicksort.o $(SRCDIR)/sort.o
SORT = sort

.PHONY: all clean test

all: $(SORT)

$(SORT): $(SORT_OBJS)
	$(CC) $(CFLAGS) -o $(SORT) $(SORT_OBJS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c include/quicksort.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(SRCDIR)/*.o $(SORT)

test:
	@./scripts/test.sh
