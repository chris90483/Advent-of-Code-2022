#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("out of memory, download more RAM\n");
        exit(1);
    }
    return ptr;
}

size_t is_visible(struct Tree* tree) {
    size_t visible;
    
    for (size_t direction = 0; direction < 4; direction++) {
        struct Tree *next_tree = tree;
        visible = 1;
        
        while ((next_tree->neighbours[direction]) != NULL) {
            if (next_tree->neighbours[direction]->height >= tree->height) {
                visible = 0;
                break;
            }
            next_tree = next_tree->neighbours[direction];
        }
        if (visible) {
            return 1;
        }
    }
    return 0;
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

    size_t amount_of_visible_trees = 0;
    for (size_t x = 0; x < vertical_forest_size; x++) {
        for (size_t y = 0; y < horizontal_forest_size; y++) {
            amount_of_visible_trees += is_visible(forest[(x * horizontal_forest_size) + y]);
        }
    }
    printf("There are %u visible trees in total.", amount_of_visible_trees);
    
    return 0;
}