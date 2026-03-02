#include "aoc.h"

// ── Helpers ───────────────────────────────────────────────────────────────────
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

// ── Part 1 ────────────────────────────────────────────────────────────────────
char *part1(Input *in) {
    
    const char *p = in->raw;
    uint64_t total = 0;

    while (*p != '\0') {
        uint64_t first_val, last_val;
        char *next;
        
        first_val = strtoull(p, &next, 10);
        if (*next != '-') break;
        
        p = next + 1;
        last_val = strtoull(p, &next, 10);
        
        // printf("Range: %llu to %llu\n", first_val, last_val);

        for (uint64_t num = first_val; num <= last_val; num++) {
            if (inv_ID_1(num)) {
                // printf("Invalid ID: %llu\n", num);
                total += num;
            }
        }
        p = next;
        while (*p == ',' || *p == ' ' || *p == '\n') {
            p++;
        }
    }
    return aoc_ll(total);
}

// ── Part 2 ────────────────────────────────────────────────────────────────────
char *part2(Input *in) {
    
    const char *p = in->raw;
    uint64_t total = 0;
    
    while (*p != '\0') {
        uint64_t first_val, last_val;
        char *next;
        
        first_val = strtoull(p, &next, 10);
        if (*next != '-') break;
        
        p = next + 1;
        last_val = strtoull(p, &next, 10);
        
        // printf("Range: %llu to %llu\n", first_val, last_val);

        for (uint64_t num = first_val; num <= last_val; num++) {
            if (inv_ID_2(num)) {
                // printf("Invalid ID: %llu\n", num);
                total += num;
            }
        }
            
        p = next;
        while (*p == ',' || *p == ' ' || *p == '\n') {
            p++;
        }
    }
    return aoc_ll(total);
}