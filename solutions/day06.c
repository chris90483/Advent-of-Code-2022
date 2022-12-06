#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 3

const char INIT_CHAR = '!'; //guaranteed to not be present in actual input
const char *CHAR_BUFFER_INIT = "!!!";

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

// this makes the inline function an available symbol.
int relative_index(int index, int offset);

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day06.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input\n");
        return 1;
    }
    
    char last_3_chars[BUFFER_SIZE];
    strncpy(last_3_chars, CHAR_BUFFER_INIT, BUFFER_SIZE);
    int i_previous_char = 0;
    size_t char_ctr = 0;
    int marker_found = 0;
    
    char current_char;
    while (fscanf(puzzle_input_file_ptr, "%c", &current_char) != EOF) {
        if (current_char == '\n') {
            strncpy(last_3_chars, CHAR_BUFFER_INIT, BUFFER_SIZE);
            i_previous_char = 0;
            char_ctr = 0;
            marker_found = 0;
            continue;
        }
        if (marker_found) {
            continue;
        }
        
        if (current_char ^ last_3_chars[               i_previous_char     ] &&
            current_char ^ last_3_chars[relative_index(i_previous_char, -1)] &&
            current_char ^ last_3_chars[relative_index(i_previous_char, -2)]) {
            // current_char is unique
            if (last_3_chars[i_previous_char] ^ last_3_chars[relative_index(i_previous_char, -1)] &&
                last_3_chars[i_previous_char] ^ last_3_chars[relative_index(i_previous_char, -2)]) {
                // last char is unique
                if (last_3_chars[relative_index(i_previous_char, -1)] ^ last_3_chars[relative_index(i_previous_char, -2)]) {
                    // 2nd and 3rd char in history are also unique, check if init characters in buffer
                    if (last_3_chars[i_previous_char                    ] != INIT_CHAR && 
                        last_3_chars[relative_index(i_previous_char, -1)] != INIT_CHAR && 
                        last_3_chars[relative_index(i_previous_char, -2)] != INIT_CHAR) {
                            printf("marker detected at position %u\n", char_ctr + 1);
                            marker_found = 1;
                    }
                }
            }
        }
        
        i_previous_char = relative_index(i_previous_char, 1);
        last_3_chars[i_previous_char] = current_char;
        char_ctr++; 
    }
    
    fclose(puzzle_input_file_ptr);
    return 0;
}