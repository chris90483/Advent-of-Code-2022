#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INPUT_LINE_LENGTH 100


char get_common_item(char *first_rucksack, char *second_rucksack, char *third_rucksack) {
    
    char seen_in_first[123];
    for (size_t i = 0; i < 123; i++) {
        seen_in_first[i] = 0;
    }
    
    char seen_in_second[123];
    for (size_t i = 0; i < 123; i++) {
        seen_in_second[i] = 0;
    }
    
    char seen_in_third[123];
    for (size_t i = 0; i < 123; i++) {
        seen_in_third[i] = 0;
    }
    
    for (size_t i = 0; i < strlen(first_rucksack); i++) {
        seen_in_first[first_rucksack[i]] = 1;
    }
    
    for (size_t i = 0; i < strlen(second_rucksack); i++) {
        seen_in_second[second_rucksack[i]] = 1;
    }
    
    for (size_t i = 0; i < strlen(third_rucksack); i++) {
        seen_in_third[third_rucksack[i]] = 1;
    }
    
    for (size_t i = 65; i <= 90; i++) {
        if (seen_in_first[i] & seen_in_second[i] & seen_in_third[i]) {
            return i;
        }
    }
    
    for (size_t i = 97; i <= 122; i++) {
        if (seen_in_first[i] & seen_in_second[i] & seen_in_third[i]) {
            return i;
        }
    }
    
    printf("No common item found in %s/%s/%s", first_rucksack, second_rucksack, third_rucksack);
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
    printf("Can't get priority for non-alpha %c", item);
    exit(1);
}

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day03.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input\n");
        return 1;
    }
    
    unsigned int priority_sum = 0;
    
    char *first_rucksack = malloc(sizeof(char) * MAX_INPUT_LINE_LENGTH + 1);
    char *second_rucksack = malloc(sizeof(char) * MAX_INPUT_LINE_LENGTH + 1);
    char *current_rucksack = malloc(sizeof(char) * MAX_INPUT_LINE_LENGTH + 1);
    size_t ctr = 0;
    
    while (fgets(current_rucksack, MAX_INPUT_LINE_LENGTH, puzzle_input_file_ptr) != NULL) {
       if (ctr == 0) {
           sprintf(first_rucksack, "%s", current_rucksack);
           ctr++;
       } else if (ctr == 1) {
           sprintf(second_rucksack, "%s", current_rucksack);
           ctr++;
       } else {
           priority_sum += get_priority(get_common_item(first_rucksack, second_rucksack, current_rucksack));
           ctr = 0;
       }
    }
    free(current_rucksack);
    printf("sum of priorities: %u\n", priority_sum);
    
    fclose(puzzle_input_file_ptr);
    return 0;
}