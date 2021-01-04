CC := gcc
CFLAGS := -Wall -O2 -g -fomit-frame-pointer -pipe
.PHONY: all clean

all: makepzi

makepzi: main.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) makepzi
