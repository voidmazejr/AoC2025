#include "aoc.h"

// ── Helpers ───────────────────────────────────────────────────────────────────


// ── Part 1 ────────────────────────────────────────────────────────────────────
char *part1(Input *in) {
   int count = 0; 

    int dx[] = {-1,-1,-1,0,0,1,1,1}; 
    int dy[] = {-1,0,1,-1,1,-1,0,1}; 
    
    for (int i = 0; i < in->line_count; i++) {
        int line_len = strlen(in->lines[i]);
        for (int j = 0; j < line_len; j++) {
            
            if (in->lines[i][j] == '@') {
                int neighbours_count = 0;

                for (int k = 0; k < 8; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];

                    //bound check
                    if (ni >= 0 && ni < in->line_count && nj >= 0 && nj < line_len) {
                        if (in->lines[ni][nj] == '@') {
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

    return aoc_int(count);
}

// ── Part 2 ────────────────────────────────────────────────────────────────────
char *part2(Input *in) {
    
    int total_removed = 0;
    int changed = 1;

    int dx[] = {-1,-1,-1,0,0,1,1,1}; 
    int dy[] = {-1,0,1,-1,1,-1,0,1}; 
    
    while (changed) {
        changed = 0;
        for (int i = 0; i < in->line_count; i++) {
            int line_len = strlen(in->lines[i]);
            for (int j = 0; j < line_len; j++) {
                
                if (in->lines[i][j] == '@') {
                    int neighbours_count = 0;
    
                    for (int k = 0; k < 8; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
    
                        //bound check + counter
                        if (ni >= 0 && ni < in->line_count && nj >= 0 && nj < line_len) {
                            if (in->lines[ni][nj] == '@' || in->lines[ni][nj] == 'X') {
                                neighbours_count++;
                            }
                        }
                    }
                    if (neighbours_count <= 3) {
                        in->lines[i][j] = 'X';
                        changed = 1;
                    } 
                }
            }
        }
        for (int i = 0; i < in->line_count; i++) {
            for (int j = 0; in->lines[i][j]; j++) {
                if (in->lines[i][j] == 'X') {
                    in->lines[i][j] = 'x';
                    total_removed++;
                }
            }
        }
    }    
    
    return aoc_int(total_removed);
}