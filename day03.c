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
    int line_count;
    char **lines = read_input_lines(day, &line_count);
    if (!lines) return;
    char *input = read_input(day);
    if (!input) return;

    // printf("Part 2 Solution:\n");
    
// -----------------------Solution Here------------------------------ 
    int MAX_TOTAL_LEN = 1000;

    char total_jolt[MAX_TOTAL_LEN];
    strcpy(total_jolt, "0"); // Initialize the running sum
    char new_total_buffer[MAX_TOTAL_LEN];


    for (int i = 0; i < line_count; i++) {
        
        int bankLenght = strlen(lines[i]);

        int *bank = malloc(bankLenght * sizeof(int));
        if (bank == NULL) {
            perror("Failed to alloc mem!");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < bankLenght; j++) {
            bank[j] = lines[i][j] - '0';
        }

        // jolt calc
        int desired_ammount = 12;

        if(bankLenght < desired_ammount) {
            free(bank);
            continue;
        }

        char max_jolt_str[desired_ammount + 1];
        max_jolt_str[desired_ammount] = '\0';

        int start_index = 0;

        for (int k = 0; k < desired_ammount; k++) {
            int end_index = bankLenght - (desired_ammount - k);

            int max_digi_val = -1;
            int max_index = start_index;

            for (int j = start_index; j <= end_index; j++) {
                if (bank[j] > max_digi_val) {
                    max_digi_val = bank[j];
                    max_index = j;
                }
                if (max_digi_val == 9) break;
            }

            max_jolt_str[k] = max_digi_val + '0';
            start_index = max_index + 1;

        }
        // --- 2. Large Number Addition: Add max_joltage_str to total_joltage ---
        
        // Indices start from the end of the strings (LSD)
        int len1 = strlen(total_jolt);
        int len2 = strlen(max_jolt_str);
        
        int i1 = len1 - 1;
        int i2 = len2 - 1;
        
        // sum_idx starts at the end of the result buffer
        int sum_idx = (len1 > len2 ? len1 : len2);
        int carry = 0;

        // Initialize the new sum string buffer
        new_total_buffer[sum_idx + 1] = '\0'; 

        // Perform addition, working backward
        while (i1 >= 0 || i2 >= 0 || carry) {
            // Get digits (or 0 if the index is out of bounds)
            int d1 = (i1 >= 0) ? total_jolt[i1--] - '0' : 0;
            int d2 = (i2 >= 0) ? max_jolt_str[i2--] - '0' : 0;
            
            int sum = d1 + d2 + carry;
            
            carry = sum / 10;
            new_total_buffer[sum_idx--] = (sum % 10) + '0';
        }
        
        // Copy the result back to total_joltage, removing any leading space/zero from the buffer
        strcpy(total_jolt, &new_total_buffer[sum_idx + 1]); 

        
        free(bank);
    } 

    printf("Part 2 Solution: %s\n", total_jolt);



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