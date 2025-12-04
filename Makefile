CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

# List your day solutions here
DAYS = day01 day02

all: $(DAYS)

day%: day%.c aoc_framework.h
	$(CC) $(CFLAGS) -o bin/$@ $<

clean:
	rm -f $(DAYS)
	rm -rf inputs/

.PHONY: all clean