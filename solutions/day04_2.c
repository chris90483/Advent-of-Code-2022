#include <stdio.h>

#define START_A 0
#define END_A 1
#define START_B 2
#define END_B 3

int has_overlap(int *ranges) {
    return ! /* it's easier to calculate the opposite. */
           ((ranges[START_A] > ranges[END_B]) || /* A comes after B */
            (ranges[END_A] < ranges[START_B]));  /* A comes before B */
}

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day04.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input\n");
        return 1;
    }
    
    int ranges_of_pairs[4];
    int amount_of_pairs_with_overlap = 0;
    while (fscanf(puzzle_input_file_ptr, "%d-%d,%d-%d\n", &ranges_of_pairs[0], &ranges_of_pairs[1], &ranges_of_pairs[2], &ranges_of_pairs[3]) != EOF) {
        amount_of_pairs_with_overlap += has_overlap(ranges_of_pairs);
    }
    printf("%d pairs have overlap.", amount_of_pairs_with_overlap);
    
    fclose(puzzle_input_file_ptr);
    return 0;
}