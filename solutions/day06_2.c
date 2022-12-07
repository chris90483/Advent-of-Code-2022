#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 13

const char INIT_CHAR = '!'; //guaranteed to not be present in actual input
const char *CHAR_BUFFER_INIT = "!!!!!!!!!!!!!";

inline int relative_index(int index, int offset) {
    size_t result;
    if (index + offset < 0) {
        return (index + BUFFER_SIZE) + offset;
    }
    if (index + offset >= BUFFER_SIZE) {
        return (index - BUFFER_SIZE) + offset;
    }
    return index + offset;
}

inline int unique_in(char c, char* buf) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (!(buf[i] ^ c)) {
            return 0;
        }
    }
    return 1;
}

// this makes the inline functions available symbols.
int relative_index(int index, int offset);
int unique_in(char c, char* buf);

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\bigboy\\day06.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input\n");
        return 1;
    }
    
    char last_13_chars[BUFFER_SIZE];
    strncpy(last_13_chars, CHAR_BUFFER_INIT, BUFFER_SIZE);
    int i_previous_char = 0;
    size_t char_ctr = 0;
    int marker_found = 0;
    
    char current_char;
    while (fscanf(puzzle_input_file_ptr, "%c", &current_char) != EOF) {
        if (current_char == '\n') {
            strncpy(last_13_chars, CHAR_BUFFER_INIT, BUFFER_SIZE);
            i_previous_char = 0;
            char_ctr = 0;
            marker_found = 0;
            continue;
        }
        if (marker_found) {
            exit(0);
        }
        
        if (unique_in(current_char, last_13_chars)) {
            // unique new candidate found, check if buffer is unique
            int buffer_is_unique = 1;
            for (int i = 0; i < BUFFER_SIZE; i++) {
                if (!buffer_is_unique) {
                    break;
                }
                char to_test = last_13_chars[i];
                last_13_chars[i] = INIT_CHAR; // don't wanna match the char we are testing
                if (!unique_in(to_test, last_13_chars)) {
                    buffer_is_unique = 0;
                }
                last_13_chars[i] = to_test; // put it back where it belongs, very tidy.
            }
            if (buffer_is_unique) {
                printf("marker detected at position %u\n", char_ctr + 1);
                marker_found = 1;
            }
        }
        
        i_previous_char = relative_index(i_previous_char, 1);
        last_13_chars[i_previous_char] = current_char;
        char_ctr++; 
    }
    
    fclose(puzzle_input_file_ptr);
    return 0;
}