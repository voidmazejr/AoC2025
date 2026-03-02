#include "aoc_framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

//-----------------------Help Functions------------------------------
// ------------------------------------------------------------------

void solve_part1(int day) {
    int line_count;
    char **lines = read_input_lines(day, &line_count);
    if (!lines) return;

    printf("Part 1 Solution:\n");

    // -----------------------Solution Here------------------------------
    
    

    // -----------------------------------------------------------------   

    free_lines(lines, line_count);
}



void solve_part2(int day) {
    int line_count;
    char **lines = read_input_lines(day, &line_count);
    if (!lines) return;
    char *input = read_input(day);
    if (!input) return;

    printf("Part 2 Solution:\n");
    
// -----------------------Solution Here------------------------------ 


// ------------------------------------------------------------------    

    free(input);
}



int main() {
    int year = 2025;
    int day = 5;

    // Download input if not already cached
    download_input(year, day);
    
    // Solve both parts
    solve_part1(day);
    printf("\n");
    solve_part2(day);
    
    return 0;
}