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
    int count = 0; 

    int dx[] = {-1,-1,-1,0,0,1,1,1}; 
    int dy[] = {-1,0,1,-1,1,-1,0,1}; 
    
    for (int i = 0; i < line_count; i++) {
        int line_len = strlen(lines[i]);
        for (int j = 0; j < line_len; j++) {
            
            if (lines[i][j] == '@') {
                int neighbours_count = 0;

                for (int k = 0; k < 8; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];

                    //bound check
                    if (ni >= 0 && ni < line_count && nj >= 0 && nj < line_len) {
                        if (lines[ni][nj] == '@') {
                            neighbours_count++;
                        }
                    }
                }
                if (neighbours_count <= 3) {
                    count++;
                } 
            }
        }
    }
    printf(" Valid @ Count: %d\n", count);
    return;

// ------------------------------------------------------------------   

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
    int count = 0; 
    int total_removed = 0;
    int changed = 1;

    int dx[] = {-1,-1,-1,0,0,1,1,1}; 
    int dy[] = {-1,0,1,-1,1,-1,0,1}; 
    
    while (changed) {
        changed = 0;
        for (int i = 0; i < line_count; i++) {
            int line_len = strlen(lines[i]);
            for (int j = 0; j < line_len; j++) {
                
                if (lines[i][j] == '@') {
                    int neighbours_count = 0;
    
                    for (int k = 0; k < 8; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
    
                        //bound check + counter
                        if (ni >= 0 && ni < line_count && nj >= 0 && nj < line_len) {
                            if (lines[ni][nj] == '@' || lines[ni][nj] == 'X') {
                                neighbours_count++;
                            }
                        }
                    }
                    if (neighbours_count <= 3) {
                        lines[i][j] = 'X';
                        changed = 1;
                    } 
                }
            }
        }
        for (int i = 0; i < line_count; i++) {
            for (int j = 0; lines[i][j]; j++) {
                if (lines[i][j] == 'X') {
                    lines[i][j] = 'x';
                    total_removed++;
                }
            }
        }
    }

    printf(" Valid @ Count: %d\n", total_removed);
    return;

// ------------------------------------------------------------------    

    free(input);
}



int main() {
    int year = 2025;
    int day = 4;

    // Download input if not already cached
    download_input(year, day);
    
    // Solve both parts
    solve_part1(day);
    printf("\n");
    solve_part2(day);
    
    return 0;
}