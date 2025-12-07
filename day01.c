#include "aoc_framework.h"
#include <stdio.h>
#include <stdlib.h>

void solve_part1(int day) {
    int line_count;
    char **lines = read_input_lines(day, &line_count);

    if (!lines) return;
    printf("Part 1 Solution:\n");

// -----------------------Solution Here------------------------------
    int count = 0;
    int curr = 50;

    for (int i = 0; i < line_count; i++) {
        int distance = atoi(lines[i] + 1);
        
        if (lines[i][0] == 'R') {
            curr = (curr + distance) % 100;
        }
        if (lines[i][0] == 'L') {
            curr = ((curr - distance) % 100 + 100) % 100;
        }
        printf("current curr %d \n", curr);
        if (curr == 0) {
            count++;
        }
    }
    printf("count: %d\n", count);

// ------------------------------------------------------------------   
    free_lines(lines, line_count);
}




void solve_part2(int day) {
    int line_count;
    char **lines = read_input_lines(day, &line_count);
    char *input = read_input(day);
    if (!input) return;

    printf("Part 2 Solution:\n");
    
// -----------------------Solution Here------------------------------ 
    int count = 0;
    int curr = 50;

    for (int i = 0; i < line_count; i++) {
        int distance = atoi(lines[i] + 1);
        int step;
        if (lines[i][0] == 'L') {
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
    printf("count: %d\n", count);

// ------------------------------------------------------------------    
    free(input);
}



int main() {
    int year = 2025;
    int day = 1;
    
    // Download input if not already cached
    download_input(year, day);
    
    // Solve both parts
    solve_part1(day);
    printf("\n");
    solve_part2(day);
    
    return 0;
}