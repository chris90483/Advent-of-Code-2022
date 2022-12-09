#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lib/util.h"

#define MAX_INPUT_LINE_LENGTH 150
#define MAX_INPUT_AMOUNT_LINES 150

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

struct Tree {
    int height;
    struct Tree **neighbours;
};

size_t scenic_score_of(struct Tree* tree) {
    size_t scenic_score = 1;
    
    for (size_t direction = 0; direction < 4; direction++) {
        struct Tree *next_tree = tree;
        size_t direction_score = 0;
        
        while ((next_tree->neighbours[direction]) != NULL) {
            direction_score++;
            if (next_tree->neighbours[direction]->height >= tree->height) {
                break;
            }
            next_tree = next_tree->neighbours[direction];
        }
        scenic_score *= direction_score;
    }
    return scenic_score;
}

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day08.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input\n");
        return 1;
    }
    
    char *lines[MAX_INPUT_AMOUNT_LINES];
    char current_line[MAX_INPUT_LINE_LENGTH];
    size_t ctr = 0;
    
    while (fgets(current_line, MAX_INPUT_LINE_LENGTH, puzzle_input_file_ptr) != NULL) {
        char *dest = safe_malloc(sizeof(char) * strlen(current_line));
        strcpy(dest, current_line);
        lines[ctr++] = dest;
    }
    
    size_t vertical_forest_size = ctr;
    size_t horizontal_forest_size = strlen(lines[0]) - 1; // minus the \n char
    struct Tree **forest = malloc(sizeof(struct Tree *) * horizontal_forest_size * vertical_forest_size);
    
    printf("forest dimensions: %u by %u\n", vertical_forest_size, horizontal_forest_size);
    
    // creating trees
    for (size_t x = 0; x < vertical_forest_size; x++) {
        for (size_t y = 0; y < horizontal_forest_size; y++) {
            struct Tree *tree = safe_malloc(sizeof(struct Tree));
            struct Tree **neighbours = safe_malloc(sizeof(struct Tree *) * 4);
            
            char height_str[2] = {lines[x][y], '\0'};
            *tree = (struct Tree) {
                atoi(height_str),
                neighbours
            };
            
            forest[(x * horizontal_forest_size) + y] = tree;
        }
    }
    
    // adding neighbours to trees
    for (size_t x = 0; x < vertical_forest_size; x++) {
        for (size_t y = 0; y < horizontal_forest_size; y++) {
            struct Tree *tree = forest[(x * horizontal_forest_size) + y];
            tree->neighbours[NORTH] = x > 0                            ? forest[(x - 1) * horizontal_forest_size + y    ] : NULL;
            tree->neighbours[EAST ] = y < (horizontal_forest_size - 1) ? forest[ x      * horizontal_forest_size + y + 1] : NULL;
            tree->neighbours[SOUTH] = x < (vertical_forest_size   - 1) ? forest[(x + 1) * horizontal_forest_size + y    ] : NULL;
            tree->neighbours[WEST ] = y > 0                            ? forest[ x      * horizontal_forest_size + y - 1] : NULL;
        }
    }

    size_t best_scenic_score = 0;
    for (size_t x = 0; x < vertical_forest_size; x++) {
        for (size_t y = 0; y < horizontal_forest_size; y++) {
            size_t candidate = scenic_score_of(forest[(x * horizontal_forest_size) + y]);
            best_scenic_score = candidate > best_scenic_score ? candidate : best_scenic_score;
        }
    }
    printf("The best scenic score is %u.", best_scenic_score);
    
    return 0;
}