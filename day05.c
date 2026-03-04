#include "aoc.h"

// ── Helpers ───────────────────────────────────────────────────────────────────
typedef struct {
    long long start;
    long long end;
} Range;

int find_in_range(long long start, long long end, long long target) {
    if (target >= start && target <= end) return 1;
    return 0; 
}

int compare_ranges(const void *a, const void *b) {
    Range *r1 = (Range *)a;
    Range *r2 = (Range *)b;
    if (r1->start != r2->start) return (r1->start > r2->start) - (r1->start < r2->start);
    return (r1->end > r2->end) - (r1->end < r2->end);
}
// ── Part 1 ────────────────────────────────────────────────────────────────────
char *part1(Input *in) {
    
    Range ranges[in->line_count];
    int range_count = 0;
    int i = 0;

    for (; i < in->line_count; i++) {
        if (strlen(in->lines[i]) == 0) break;
        

        int count;
        long long *nums = aoc_ints(in->lines[i], &count);
        if (count == 2) {
            long long n1 = nums[0];
            long long n2 = nums[1];
            if (n2 < 0) n2 = -n2;
            if (n1 < 0) n1 = -n1;

            ranges[range_count].start = n1;
            ranges[range_count].end = n2;
            range_count++;

            // printf("Range: %lld-%lld\n", ranges[range_count-1].start, ranges[range_count-1].end);
        }
        free(nums);
    }

    i++;
    int valid_count = 0;

    for (; i < in->line_count; i++) {
        int count;
        long long *nums = aoc_ints(in->lines[i], &count);
        
        if(count == 0) {
            free(nums);
            continue;
        }
        
        if (count == 1) {
            long long target = nums[0];

            for (int j = 0; j < range_count; j++) {
                if (find_in_range(ranges[j].start, ranges[j].end, target)) {
                    valid_count++;
                    break;
                }
            }
        }
        free(nums);
    }
    
    return aoc_ll(valid_count);
}

// ── Part 2 ────────────────────────────────────────────────────────────────────
char *part2(Input *in) {
    
    Range ranges[in->line_count];
    int range_count = 0;
    
    for (int i = 0; i < in->line_count; i++) {
        if (strlen(in->lines[i]) <= 0) break;
        int count;
        long long *nums = aoc_ints(in->lines[i], &count);

        if (count == 2) {
            long long n1 = llabs(nums[0]);
            long long n2 = llabs(nums[1]);

            ranges[range_count].start = n1;
            ranges[range_count].end = n2;
            range_count++;

            // printf("Range: %lld-%lld\n", ranges[range_count-1].start, ranges[range_count-1].end);
        }   
        free(nums);
    }
    qsort(ranges, range_count, sizeof(Range), compare_ranges);

    long long total_valid = 0;
    if (range_count > 0) {
        long long current_start = ranges[0].start;
        long long current_end = ranges[0].end;

        for (int i = 1; i < range_count; i++) {
            if (ranges[i].start <= current_end) {
                if (ranges[i].end > current_end) {
                    current_end = ranges[i].end;
                }
            } else {
                total_valid += (current_end - current_start + 1);
                current_start = ranges[i].start;
                current_end = ranges[i].end;
            }
        }
        total_valid += (current_end - current_start + 1);
    }

    return aoc_ll(total_valid);
}