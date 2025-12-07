#include "aoc_framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//-----------------------Help Functions------------------------------

// ------------------------------------------------------------------


void solve_part1(int day) {
    int line_count;
    char **lines = read_input_lines(day, &line_count);
    if (!lines) return;

    printf("Part 1 Solution:\n");

// -----------------------Solution Here------------------------------
    
    int result = 0;

    for (int i = 0; i < line_count; i++) {
        
        int strLenght = strlen(lines[i]);

        int *arr = malloc(strLenght * sizeof(int));
        if (arr == NULL) {
            perror("Failed to alloc mem!");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < strLenght; j++) {
            arr[j] = lines[i][j] - '0';
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
        printf("Max Joltage for Arr %d: %d \n", i + 1, max_jolt);
        result += max_jolt;
    
        free(arr);
    }
    printf("Total = %d\n", result);

// ------------------------------------------------------------------   

    free_lines(lines, line_count);
}





void solve_part2(int day) {
    char *input = read_input(day);
    if (!input) return;

    // printf("Part 2 Solution:\n");
    
// -----------------------Solution Here------------------------------ 




// ------------------------------------------------------------------    

    free(input);
}



int main() {
    int year = 2025;
    int day = 3;

    // Download input if not already cached
    download_input(year, day);
    
    // Solve both parts
    solve_part1(day);
    printf("\n");
    solve_part2(day);
    
    return 0;
}