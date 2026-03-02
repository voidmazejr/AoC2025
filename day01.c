#include "aoc.h"

// ── Helpers ───────────────────────────────────────────────────────────────────


// ── Part 1 ────────────────────────────────────────────────────────────────────
char *part1(Input *in) {
    (void)in;

    int count = 0;
    int curr = 50;

    for (int i = 0; i < in->line_count; i++) {
        int distance = atoi(in->lines[i] + 1);
        
        if (in->lines[i][0] == 'R') {
            curr = (curr + distance) % 100;
        }
        if (in->lines[i][0] == 'L') {
            curr = ((curr - distance) % 100 + 100) % 100;
        }
        // printf("current curr %d \n", curr);
        if (curr == 0) {
            count++;
        }
    }

    return aoc_int(count);
}

// ── Part 2 ────────────────────────────────────────────────────────────────────
char *part2(Input *in) {
    
    int count = 0;
    int curr = 50;

    for (int i = 0; i < in->line_count; i++) {
        int distance = atoi(in->lines[i] + 1);
        int step;
        if (in->lines[i][0] == 'L') {
            step = -1;
        } else {
            step = 1;
        }
        int fullCycles = distance / 100;
        count += fullCycles;
        int remainder = distance % 100;

        for (int j = 0; j < remainder; j++) {
            curr = (curr + step + 100) % 100;
            if (curr == 0) {
                count++;
            }
        }
    }
    
    return aoc_int(count);
}