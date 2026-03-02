#include "aoc.h"

// ── Helpers ───────────────────────────────────────────────────────────────────


// ── Part 1 ────────────────────────────────────────────────────────────────────
char *part1(Input *in) {

    int result = 0;

    for (int i = 0; i < in->line_count; i++) {
        
        int strLenght = strlen(in->lines[i]);

        int *arr = malloc(strLenght * sizeof(int));
        if (arr == NULL) {
            perror("Failed to alloc mem!");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < strLenght; j++) {
            arr[j] = in->lines[i][j] - '0';
        }

        // check for the 2 biggest nums:
        int max_jolt = 0;
        for (int j = 0; j < strLenght - 1; j++) {
            int first_big = arr[j];

            int max_second_big = 0;

            for (int k = j + 1; k < strLenght; k++) {
                int second_big = arr[k];

                if (second_big > max_second_big) {
                    max_second_big = second_big;
                }
            }
            // int concatenation
            int current_jolt = first_big * 10 + max_second_big;

            if (current_jolt > max_jolt) {
                max_jolt = current_jolt;
            
            }
        }
        // printf("Max Joltage for Arr %d: %d \n", i + 1, max_jolt);
        result += max_jolt;
    
        free(arr);
    }
    
    return aoc_ll(result);
}

// ── Part 2 ────────────────────────────────────────────────────────────────────
char *part2(Input *in) {
    
    unsigned long long total_sum = 0;
    const int TARGET_LEN = 12;

    for (int i = 0; i < in->line_count; i++) {
        char *line = in->lines[i];
        int n = strlen(line);
        if (n < TARGET_LEN) continue;

        char result_digits[13]; 
        int current_start = 0;

        // Greedy selection of 12 digits
        for (int k = 0; k < TARGET_LEN; k++) {
            int max_digit = -1;
            int best_idx = current_start;

            // We must leave (TARGET_LEN - 1 - k) digits available after this one
            int look_ahead_limit = n - (TARGET_LEN - k);

            for (int j = current_start; j <= look_ahead_limit; j++) {
                int val = line[j] - '0';
                if (val > max_digit) {
                    max_digit = val;
                    best_idx = j;
                    if (max_digit == 9) break; 
                }
            }
            result_digits[k] = max_digit + '0';
            current_start = best_idx + 1;
        }
        result_digits[TARGET_LEN] = '\0';

        // Convert the 12-digit string to a number and add to total
        total_sum += strtoull(result_digits, NULL, 10);
    }
 
    return aoc_ll(total_sum);
}