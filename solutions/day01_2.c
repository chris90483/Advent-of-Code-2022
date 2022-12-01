#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct IndexedValue {
    int index;
    int value;
};

struct IndexedValue get_highest(int *nums, int length) {
    struct IndexedValue highest = {0, nums[0]};
    int i = 0;
    for (int i = 0; i < length; i++) {
        highest = highest.value > nums[i] ? highest : (struct IndexedValue){i, nums[i]};
    }
    return highest;
}

int top_3_calorie_count(int *elves, int number_of_elves) {
    int result = 0;
    for (int _ = 0; _ < 3; _++) {
        struct IndexedValue highest = get_highest(elves, number_of_elves);
        result += highest.value;
        elves[highest.index] = 0;
    }
    return result;
}

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day01.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input");
        return 1;
    }
    int MAX_INPUT_LINE_LENGTH = 10;
    int MAX_ELVES_ACCEPTED = 1000;
    
    
    int number_of_elves = 0;
    int elf_rations = 0;
    int elves[MAX_ELVES_ACCEPTED];
    
    char current_line[MAX_INPUT_LINE_LENGTH];
    while (fgets(current_line, MAX_INPUT_LINE_LENGTH, puzzle_input_file_ptr) != NULL) {
        if (strlen(current_line) > 1) {
            elf_rations += atoi(current_line);
        } else {
            elves[number_of_elves] = elf_rations;
            number_of_elves++;
            if (number_of_elves >= MAX_ELVES_ACCEPTED) {
                printf("Too many elves!");
                return 1;
            }
            elf_rations = 0;
        }
    }
    printf("parsed %d elves.\n", number_of_elves);
    printf("Top 3 calorie count: %d\n", top_3_calorie_count(elves, number_of_elves));
    
    fclose(puzzle_input_file_ptr);
    return 0;
}