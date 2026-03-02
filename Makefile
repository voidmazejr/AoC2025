# ── Advent of Code Makefile ──────────────────────────────────────────────────
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2
BINDIR  = bin
INPDIR  = inputs

YEAR ?= 2025
DAY  ?= 01

# Auto-discover all dayXX.c files
SRCS := $(wildcard day*.c)
BINS := $(patsubst %.c,$(BINDIR)/%,$(SRCS))

# ── Targets ──────────────────────────────────────────────────────────────────

.PHONY: all clean run new

all: $(BINDIR) $(BINS)

$(BINDIR):
	@mkdir -p $(BINDIR)

# Extract numeric day from filename: day01 → 1, day05 → 5
# Passed to the compiler so aoc.h can use YEAR/DAY without #defines in each file
$(BINDIR)/day%: day%.c aoc.h | $(BINDIR)
	$(CC) $(CFLAGS) -DYEAR=$(YEAR) -DDAY=$(shell echo $* | sed 's/^0*//') -o $@ $<

# ── Run a specific day ────────────────────────────────────────────────────────
# make run DAY=01            → real input
# make run DAY=01 EXAMPLE=1  → example input (inputs/day01_example.txt)

run: $(BINDIR)/day$(DAY)
ifdef EXAMPLE
	./$(BINDIR)/day$(DAY) -e
else
	./$(BINDIR)/day$(DAY)
endif

# ── Scaffold a new day ────────────────────────────────────────────────────────
# make new DAY=05   → creates day05.c from template

new:
ifndef DAY
	$(error Usage: make new DAY=01)
endif
	@if [ -f "day$(DAY).c" ]; then \
		echo "day$(DAY).c already exists — not overwriting."; \
	else \
		cp template.c day$(DAY).c; \
		echo "Created day$(DAY).c"; \
	fi

# ── Clean ─────────────────────────────────────────────────────────────────────

clean:
	rm -rf $(BINDIR)

clean-inputs:
	rm -rf $(INPDIR)