#include "aoc_framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//-----------------------Help Functions------------------------------
bool inv_ID_1(uint64_t num) {
    char str[32];
    sprintf(str, "%llu", num);
    
    int len = strlen(str);
    
    // Muss gerade Länge haben
    if (len % 2 != 0) {
        return false;
    }
    
    int half = len / 2;
    
    // Vergleiche erste Hälfte mit zweiter Hälfte
    for (int i = 0; i < half; i++) {
        if (str[i] != str[half + i]) {
            return false;
        }
    }
    
    return true;
}

bool inv_ID_2(uint64_t num) {
    char str[32];
    sprintf(str, "%llu", num);
    int len = strlen(str);

    if (len < 2) {
        return false;
    }

    for (int pattern_len = 1; pattern_len <= len / 2; pattern_len++) {
        if (len % pattern_len != 0) {
            continue;
        }

        bool repeats = true;
        for (int i = pattern_len; i < len; i++) {
            if (str[i] != str[i % pattern_len]) {
                repeats = false; 
                break;
            }
        }
        if (repeats) {
            return true;
        }
    }
    return false;
} 
// ------------------------------------------------------------------


void solve_part1(int day) {
    char *input = read_input(day);
    int line_count;
    char **lines = read_input_lines(day, &line_count);
    if (!lines) return;

    printf("Part 1 Solution:\n");

// -----------------------Solution Here------------------------------
    const char *p = input;
    uint64_t total = 0;
    
    while (*p != '\0') {
        uint64_t first_val, last_val;
        char *next;
        
        first_val = strtoull(p, &next, 10);
        if (*next != '-') break;
        
        p = next + 1;
        last_val = strtoull(p, &next, 10);
        
        printf("Range: %llu to %llu\n", first_val, last_val);

        for (uint64_t num = first_val; num <= last_val; num++) {
            if (inv_ID_1(num)) {
                printf("Invalid ID: %llu\n", num);
                total += num;
            }
        }
            
        
        p = next;
        while (*p == ',' || *p == ' ' || *p == '\n') {
            p++;
        }
    }
    printf("Total sum of invalid IDs: %llu\n", total);

// ------------------------------------------------------------------   

    free_lines(lines, line_count);
}




void solve_part2(int day) {
    char *input = read_input(day);
    if (!input) return;

    printf("Part 2 Solution:\n");
    
// -----------------------Solution Here------------------------------ 
    const char *p = input;
    uint64_t total = 0;
    
    while (*p != '\0') {
        uint64_t first_val, last_val;
        char *next;
        
        first_val = strtoull(p, &next, 10);
        if (*next != '-') break;
        
        p = next + 1;
        last_val = strtoull(p, &next, 10);
        
        printf("Range: %llu to %llu\n", first_val, last_val);

        for (uint64_t num = first_val; num <= last_val; num++) {
            if (inv_ID_2(num)) {
                printf("Invalid ID: %llu\n", num);
                total += num;
            }
        }
            
        
        p = next;
        while (*p == ',' || *p == ' ' || *p == '\n') {
            p++;
        }
    }
    printf("Total sum of invalid IDs: %llu\n", total);

// ------------------------------------------------------------------    

    free(input);
}



int main() {
    int year = 2025;
    int day = 2;

    // Download input if not already cached
    download_input(year, day);
    
    // Solve both parts
    solve_part1(day);
    printf("\n");
    solve_part2(day);
    
    return 0;
}