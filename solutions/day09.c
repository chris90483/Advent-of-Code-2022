#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "lib/util.h"

#define MAX_INPUT_AMOUNT_LINES 100
#define MAX_DISTANCE_FROM_ORIGIN 1000

#define X_COORD_BITMASK ((unsigned long) ULONG_MAX / pow(2, sizeof(unsigned long) * 4))

#define UP 'U'
#define RIGHT 'R'
#define DOWN 'D'
#define LEFT 'L'

struct Rope {
    int head_x;
    int head_y;
    int tail_x;
    int tail_y;
};

struct Instruction {
    char direction;
    unsigned int amount;
};

struct Coords {
    unsigned int x;
    unsigned int y;
};

unsigned long to_index_hash(struct Coords *coords) {
    /*
    M = MAX_DISTANCE_FROM_ORIGIN
    -M . . 0 . . M
    .  .
    .    .
    0      0
    .        .
    .          .
    M            M
    */
    unsigned long x_component = (coords->x + MAX_DISTANCE_FROM_ORIGIN);
    unsigned long y_component = (coords->y + MAX_DISTANCE_FROM_ORIGIN);
    
    return x_component + (y_component << sizeof(unsigned long) * 4);
}

struct Coords *to_coords(unsigned long index_hash) {
    return (struct Coords) {
        index_hash & X_COORD_BITMASK,
        index_hash >> (sizeof(unsigned long) * 4)
    };
}

/* int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\examples\\day09.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input\n");
        return 1;
    }
    
    char next_direction;
    unsigned int next_amount;
    size_t line_ctr = 0;
    struct Instruction *instructions = safe_malloc(sizeof(struct Instruction *) * MAX_INPUT_AMOUNT_LINES);

    while (fscanf(puzzle_input_file_ptr, "%c %u\n", &next_direction, &next_amount) != EOF) {
        line_ctr++;
        if (line_ctr > MAX_INPUT_AMOUNT_LINES) {
            printf("Too many input lines! Maximum set at %u", MAX_INPUT_AMOUNT_LINES);
            exit(1);
        }
        struct Instruction instruction = (struct Instruction) {
            next_direction,
            next_amount
        };
        
        instructions[line_ctr - 1] = instruction;
    }
    
    struct Rope rope = (struct Rope) {0,0,0,0};
    
    // hash table that for any given coord (encoded in the index) gives if this location has been visited by the tail.
    unsigned long *visited_by_tail = malloc(sizeof(unsigned long) * MAX_DISTANCE_FROM_ORIGIN * MAX_DISTANCE_FROM_ORIGIN * 4);
    
    for (size_t i = 0; i < line_ctr; i++) {
        
    }
    return 0;
}
*/