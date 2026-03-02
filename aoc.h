// aoc.h  –  Advent of Code framework for C
// Usage: #define YEAR 2025 / #define DAY 1 / #include "aoc.h"
// Then implement:  char *part1(Input *in)  and  char *part2(Input *in)

#ifndef AOC_H
#define AOC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>

// ─────────────────────────────────────────────────────────────────────────────
//  Terminal colors (auto-disabled when not a TTY)
// ─────────────────────────────────────────────────────────────────────────────
#ifdef _WIN32
  #define _AOC_RED    ""
  #define _AOC_GREEN  ""
  #define _AOC_YELLOW ""
  #define _AOC_CYAN   ""
  #define _AOC_BOLD   ""
  #define _AOC_RESET  ""
#else
  #define _AOC_RED    "\033[0;31m"
  #define _AOC_GREEN  "\033[0;32m"
  #define _AOC_YELLOW "\033[0;33m"
  #define _AOC_CYAN   "\033[0;36m"
  #define _AOC_BOLD   "\033[1m"
  #define _AOC_RESET  "\033[0m"
#endif

// ─────────────────────────────────────────────────────────────────────────────
//  Input struct
// ─────────────────────────────────────────────────────────────────────────────
typedef struct {
    char  *raw;         // full file content (null-terminated)
    long   raw_len;     // byte length of raw
    char **lines;       // individual lines (newlines stripped)
    int    line_count;
    int    cols;        // length of first line (handy for grids)
    int    day;
    int    year;
} Input;

// ─────────────────────────────────────────────────────────────────────────────
//  Answer helpers
//  Return aoc_fmt(...) from your part1 / part2 functions.
//  For integer answers you can return aoc_int(n) or aoc_ll(n).
// ─────────────────────────────────────────────────────────────────────────────
static char _aoc_answer_buf[128];

#define aoc_fmt(fmt, ...) \
    (snprintf(_aoc_answer_buf, sizeof(_aoc_answer_buf), fmt, ##__VA_ARGS__), \
     _aoc_answer_buf)

#define aoc_int(n)   aoc_fmt("%d",   (int)(n))
#define aoc_ll(n)    aoc_fmt("%lld", (long long)(n))
#define aoc_ull(n)   aoc_fmt("%llu", (unsigned long long)(n))
#define aoc_str(s)   (s)   // pass through — just return your char*

// ─────────────────────────────────────────────────────────────────────────────
//  Iteration helpers
// ─────────────────────────────────────────────────────────────────────────────

// Loop over every line:   EACH_LINE(in, line) { use line->str, line->i }
typedef struct { char *str; int i; } _AocLine;
#define EACH_LINE(in, var)                                    \
    for (_AocLine var = {(in)->lines[0], 0};                  \
         var.i < (in)->line_count;                            \
         var.i++, var.str = (var.i < (in)->line_count)        \
                             ? (in)->lines[var.i] : NULL)

// Quick grid cell access (no bounds check — add your own if needed)
#define GRID_AT(in, row, col)  ((in)->lines[row][col])
#define IN_BOUNDS(in, row, col) \
    ((row) >= 0 && (row) < (in)->line_count && \
     (col) >= 0 && (col) < (int)strlen((in)->lines[row]))

// Parse all integers from a string into a heap array; sets *count.
// Caller must free().
static long long *aoc_ints(const char *s, int *count) __attribute__((unused));  
static long long *aoc_ints(const char *s, int *count) { 
    int cap = 16, n = 0;
    long long *arr = (long long *)malloc(cap * sizeof(long long));
    const char *p = s;
    while (*p) {
        while (*p && !isdigit((unsigned char)*p) && *p != '-') p++;
        if (!*p) break;
        char *end;
        long long v = strtoll(p, &end, 10);
        if (end == p) { p++; continue; }
        if (n == cap) arr = (long long *)realloc(arr, (cap *= 2) * sizeof(long long));
        arr[n++] = v;
        p = end;
    }
    *count = n;
    return arr;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Internal: file I/O
// ─────────────────────────────────────────────────────────────────────────────
static int _aoc_file_exists(const char *path) {
    struct stat s;
    return stat(path, &s) == 0;
}

static char *_aoc_read_file(const char *path, long *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);
    char *buf = (char *)malloc(sz + 1);
    if (!buf) { fclose(f); return NULL; }
    fread(buf, 1, sz, f);
    buf[sz] = '\0';
    fclose(f);
    if (out_len) *out_len = sz;
    return buf;
}

static char **_aoc_split_lines(const char *raw, int *count_out) {
    // count lines
    int n = 0;
    for (const char *p = raw; *p; p++) if (*p == '\n') n++;
    int len = (int)strlen(raw);
    if (len > 0 && raw[len - 1] != '\n') n++;  // no trailing newline
    if (n == 0) { *count_out = 0; return NULL; }

    char **lines = (char **)malloc(n * sizeof(char *));
    int i = 0;
    const char *start = raw;
    for (const char *p = raw; ; p++) {
        if (*p == '\n' || *p == '\0') {
            int llen = (int)(p - start);
            if (llen > 0 && start[llen - 1] == '\r') llen--;  // strip \r
            char *line = (char *)malloc(llen + 1);
            memcpy(line, start, llen);
            line[llen] = '\0';
            lines[i++] = line;
            start = p + 1;
        }
        if (*p == '\0') break;
    }
    *count_out = i;
    return lines;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Internal: download
// ─────────────────────────────────────────────────────────────────────────────
static char *_aoc_read_session(void) {
    FILE *f = fopen("session.txt", "r");
    if (!f) {
        fprintf(stderr,
            _AOC_RED "Error:" _AOC_RESET
            " session.txt not found. Create it with your AoC session cookie.\n");
        return NULL;
    }
    char *s = (char *)malloc(512);
    if (!fgets(s, 512, f)) { fclose(f); free(s); return NULL; }
    s[strcspn(s, "\r\n")] = '\0';
    fclose(f);
    return s;
}

static int _aoc_download(int year, int day, const char *dest) {
    char *session = _aoc_read_session();
    if (!session) return 0;

#ifdef _WIN32
    _mkdir("inputs");
#else
    system("mkdir -p inputs");
#endif

    char cmd[1024];
    snprintf(cmd, sizeof(cmd),
        "curl -sf --cookie \"session=%s\" -A \"github.com/aoc-user\" "
        "-o \"%s\" \"https://adventofcode.com/%d/day/%d/input\"",
        session, dest, year, day);
    free(session);

    int rc = system(cmd);
    if (rc != 0 || !_aoc_file_exists(dest)) {
        fprintf(stderr, _AOC_RED "Download failed." _AOC_RESET
                " Check session.txt and your internet connection.\n");
        return 0;
    }
    // Sanity check: AoC returns an HTML error page if session is invalid
    long sz = 0;
    char *raw = _aoc_read_file(dest, &sz);
    if (raw && sz < 50 && strstr(raw, "Please")) {
        fprintf(stderr, _AOC_RED "Error:" _AOC_RESET
                " Received error page — session cookie may be expired.\n");
        free(raw);
        remove(dest);
        return 0;
    }
    free(raw);
    return 1;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Internal: load input
// ─────────────────────────────────────────────────────────────────────────────
static Input *_aoc_load(int year, int day, int use_example) {
    char path[256];
    if (use_example)
        snprintf(path, sizeof(path), "inputs/day%02d_example.txt", day);
    else
        snprintf(path, sizeof(path), "inputs/day%02d.txt", day);

    if (!use_example && !_aoc_file_exists(path)) {
        printf(_AOC_CYAN "→" _AOC_RESET " Fetching input for %d day %d…\n",
               year, day);
        if (!_aoc_download(year, day, path)) return NULL;
        printf(_AOC_GREEN "✓" _AOC_RESET " Saved to %s\n\n", path);
    }

    if (!_aoc_file_exists(path)) {
        if (use_example)
            fprintf(stderr,
                _AOC_YELLOW "No example input found." _AOC_RESET
                " Create inputs/day%02d_example.txt\n", day);
        else
            fprintf(stderr,
                _AOC_RED "Input file not found:" _AOC_RESET " %s\n", path);
        return NULL;
    }

    long raw_len = 0;
    char *raw = _aoc_read_file(path, &raw_len);
    if (!raw) { perror("read"); return NULL; }

    int line_count = 0;
    char **lines = _aoc_split_lines(raw, &line_count);

    Input *in = (Input *)calloc(1, sizeof(Input));
    in->raw        = raw;
    in->raw_len    = raw_len;
    in->lines      = lines;
    in->line_count = line_count;
    in->cols       = (line_count > 0) ? (int)strlen(lines[0]) : 0;
    in->day        = day;
    in->year       = year;
    return in;
}

static void _aoc_free(Input *in) {
    if (!in) return;
    for (int i = 0; i < in->line_count; i++) free(in->lines[i]);
    free(in->lines);
    free(in->raw);
    free(in);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Internal: timing
// ─────────────────────────────────────────────────────────────────────────────
static double _aoc_ms(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) * 1e3 + (b.tv_nsec - a.tv_nsec) / 1e6;
}

// ─────────────────────────────────────────────────────────────────────────────
//  User-defined (implemented in each dayXX.c)
// ─────────────────────────────────────────────────────────────────────────────
char *part1(Input *in);
char *part2(Input *in);

// ─────────────────────────────────────────────────────────────────────────────
//  main  — generated once per binary via #include "aoc.h"
//  Requires:  #define YEAR 2025
//             #define DAY  1
//  Optional:  ./binary          → real input
//             ./binary -e       → example input (inputs/day01_example.txt)
// ─────────────────────────────────────────────────────────────────────────────
#ifndef AOC_NO_MAIN
#ifndef YEAR
  #define YEAR 0
#endif
#ifndef DAY
  #define DAY 0
#endif

int main(int argc, char *argv[]) {
    int use_example = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--example") == 0)
            use_example = 1;
    }

    printf(_AOC_BOLD "── Advent of Code %d  Day %d " _AOC_RESET, YEAR, DAY);
    if (use_example) printf(_AOC_YELLOW "[example input]" _AOC_RESET);
    printf("\n\n");

    Input *in = _aoc_load(YEAR, DAY, use_example);
    if (!in) return 1;

    printf("   Input: %d lines  (%ld bytes)\n\n", in->line_count, in->raw_len);

    // ── Part 1 ──
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    char *ans1 = part1(in);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double ms1 = _aoc_ms(t0, t1);

    if (ans1)
        printf("   " _AOC_BOLD "Part 1:" _AOC_RESET "  "
               _AOC_GREEN "%s" _AOC_RESET
               "  " _AOC_CYAN "(%.2f ms)" _AOC_RESET "\n", ans1, ms1);
    else
        printf("   " _AOC_BOLD "Part 1:" _AOC_RESET "  "
               _AOC_YELLOW "(not implemented)" _AOC_RESET "\n");

    // ── Part 2 ──
    clock_gettime(CLOCK_MONOTONIC, &t0);
    char *ans2 = part2(in);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double ms2 = _aoc_ms(t0, t1);

    if (ans2)
        printf("   " _AOC_BOLD "Part 2:" _AOC_RESET "  "
               _AOC_GREEN "%s" _AOC_RESET
               "  " _AOC_CYAN "(%.2f ms)" _AOC_RESET "\n", ans2, ms2);
    else
        printf("   " _AOC_BOLD "Part 2:" _AOC_RESET "  "
               _AOC_YELLOW "(not implemented)" _AOC_RESET "\n");

    printf("\n");
    _aoc_free(in);
    return 0;
}
#endif  // AOC_NO_MAIN

#endif  // AOC_H