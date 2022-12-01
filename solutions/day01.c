#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int highest_calorie_count(int *elves, int number_of_elves) {
    int highest = 0;
    int i = 0;
    while (i < number_of_elves) {
        highest = highest > (*elves) ? highest : (*elves);
        elves++;
        i++;
    }
    return highest;
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
    printf("Highest calorie count: %d\n", highest_calorie_count(elves, number_of_elves));
    
    fclose(puzzle_input_file_ptr);
    return 0;
}