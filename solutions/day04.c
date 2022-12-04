#include <stdio.h>

#define START_A 0
#define END_A 1
#define START_B 2
#define END_B 3

int is_contained_in_other(int *ranges) {
    return (ranges[START_A] >= ranges[START_B] && ranges[END_A] <= ranges[END_B]) || /* A contained in B */
           (ranges[START_A] <= ranges[START_B] && ranges[END_A] >= ranges[END_B]);   /* B contained in A */ 
}

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day04.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input\n");
        return 1;
    }
    
    int ranges_of_pairs[4];
    int amount_of_pairs_fully_contained = 0;
    while (fscanf(puzzle_input_file_ptr, "%d-%d,%d-%d\n", &ranges_of_pairs[0], &ranges_of_pairs[1], &ranges_of_pairs[2], &ranges_of_pairs[3]) != EOF) {
        amount_of_pairs_fully_contained += is_contained_in_other(ranges_of_pairs);
    }
    printf("%d pairs have full containment.", amount_of_pairs_fully_contained);
    
    fclose(puzzle_input_file_ptr);
    return 0;
}