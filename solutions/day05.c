#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT_LINE_LENGTH 100
#define MAX_STACKS 10
#define MAX_INSTRUCTIONS 1000
#define NOTHING '!'

struct Stack {
    char top_crate_content;
    struct Stack *rest_of_the_stack;
};

struct Instruction {
    int amount_to_move;
    int source_stack;
    int destination_stack;
};

// for debugging purposes
char *show_stack(struct Stack *stack) {
    char *result = malloc(sizeof(char) * MAX_INPUT_LINE_LENGTH);
    size_t i = 0;
    while (stack->top_crate_content != NOTHING) {
        result[i++] = stack->top_crate_content;
        result[i++] = '<';
        result[i++] = '-';
        stack = stack->rest_of_the_stack;
    }
    result[i - 2] = '\0'; // terminates the string and removes the last '<-'
    if (i == 0) {
        return "Empty stack";
    }
    return result;
}

char *get_top_contents(struct Stack **stacks) {
    char *result = malloc(sizeof(char) * MAX_STACKS);
    for (size_t i = 0; i < MAX_STACKS; i ++ ) {
        result[i] = stacks[i]->top_crate_content;
    }
    result[MAX_STACKS] = '\0'; // terminates the string
    return result;
}

void execute_instruction(struct Instruction *instruction, struct Stack **stacks) {
    for (size_t i = 0; i < instruction->amount_to_move; i++) {
        struct Stack *to_move = stacks[instruction->source_stack - 1];
        
        // create updated destination stack
        struct Stack *new_destination_stack = malloc(sizeof(struct Stack));
        new_destination_stack->top_crate_content = to_move->top_crate_content;
        new_destination_stack->rest_of_the_stack = stacks[instruction->destination_stack - 1];
        
        // put updated stack on destination
        stacks[instruction->destination_stack - 1] = new_destination_stack;
        
        // remove top from source, free the memory
        stacks[instruction->source_stack - 1] = to_move->rest_of_the_stack;
        free(to_move);
    }
}

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day05.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input\n");
        return 1;
    }
    
    char current_line[MAX_INPUT_LINE_LENGTH];
    
    // first we make some empty stacks and allocate an instruction list.
    struct Stack *stacks[MAX_STACKS];
    for (int i = 0; i < MAX_STACKS; i++) {
        struct Stack *empty_stack = malloc(sizeof(struct Stack));
        empty_stack->top_crate_content = NOTHING;
        empty_stack->rest_of_the_stack = NULL;
        stacks[i] = empty_stack;
    }
    struct Instruction instructions[MAX_INSTRUCTIONS];
    size_t instruction_ctr = 0;
    
    // parse the puzzle input.
    while (fgets(current_line, MAX_INPUT_LINE_LENGTH, puzzle_input_file_ptr) != NULL) {
       size_t current_line_length = strlen(current_line);
       if (current_line[0] == '\n' || current_line_length == 1) {
           // stack number annotation portion, ignore these lines.
           continue;
       }
       if (current_line[0] == 'm') {
           // line starts with 'move', parse an instruction
           struct Instruction instruction = {0, 0, 0};
           sscanf(current_line, "move %d from %d to %d", &instruction.amount_to_move,
                                                         &instruction.source_stack,
                                                         &instruction.destination_stack);
           instructions[instruction_ctr] = instruction;
           instruction_ctr++;
           
       } else {
           // stack definition
           for (int i = 0; i < current_line_length; i += 4) {
               if (current_line[i] == '[') {
                   struct Stack *empty_stack = malloc(sizeof(struct Stack));
                   empty_stack->top_crate_content = NOTHING;
                   empty_stack->rest_of_the_stack = NULL;
                   
                   struct Stack *stack_to_insert_into = stacks[i / 4];
                   while (stack_to_insert_into->top_crate_content != NOTHING) {
                       stack_to_insert_into = stack_to_insert_into->rest_of_the_stack;
                   }
                   stack_to_insert_into->top_crate_content = current_line[i + 1];
                   stack_to_insert_into->rest_of_the_stack = empty_stack;
               }
           }
       }
    }
    
    for (size_t i = 0; i < instruction_ctr; i++) {
        execute_instruction(&instructions[i], stacks);
    }
    
    for (size_t i = 0; i < MAX_STACKS; i++) {
        char *str = show_stack(stacks[i]);
        printf("stack %d: %s\n", i + 1, str);
        free(str);
    }
    
    printf("Top contents (! means empty stack): %s\n", get_top_contents(stacks));
    
    
    fclose(puzzle_input_file_ptr);
    return 0;
}