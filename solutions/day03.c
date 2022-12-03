#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INPUT_LINE_LENGTH 100

char get_duplicate_item(char *rucksack) {
    size_t amount_of_items_in_rucksack = strlen(rucksack) - 1; // minus the \n character.
    size_t index_of_second_compartment_start = (size_t)ceil(((float)amount_of_items_in_rucksack) / 2.0f);
    
    char seen[123]; // able to store a-zA-Z and stuff inbetween for convenience
    for (size_t i = 0; i < 123; i++) {
        seen[i] = 0;
    }
    
    for (size_t i = 0; i < index_of_second_compartment_start; i++) {
        seen[rucksack[i]] = 1;
    }
    
    for (size_t i = index_of_second_compartment_start; i < amount_of_items_in_rucksack; i++) {
        if (seen[rucksack[i]]) {
            return rucksack[i];
        }
    }
    printf("No duplicate found in %s", rucksack);
    exit(1);
}

unsigned int get_priority(char item) {
    if (item >= 65 && item <= 90) {
        // A - Z: 27 - 52
        return item - 38;
    }
    if (item >= 97 && item <= 122) {
        // a - z: 1 - 26
        return item - 96;
    }
    printf("Can't get priority for non-alpha %s", item);
    exit(1);
}

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day03.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input\n");
        return 1;
    }
    
    unsigned int priority_sum = 0;
    char current_line[MAX_INPUT_LINE_LENGTH];
    while (fgets(current_line, MAX_INPUT_LINE_LENGTH, puzzle_input_file_ptr) != NULL) {
       priority_sum += get_priority(get_duplicate_item(current_line));
    }
    printf("sum of priorities: %u\n", priority_sum);
    
    fclose(puzzle_input_file_ptr);
    return 0;
}