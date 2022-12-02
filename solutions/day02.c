#include <stdio.h>

unsigned int get_round_score(char player_1_move, char player_2_move) {
    // the "shape score" is already encoded in the two LSBs of 'A', 'B' and 'C'.
    player_1_move = player_1_move & 3; 
    player_2_move = (player_2_move - 23) & 3; // convert X/Y/Z to A/B/C first
    if (player_1_move == player_2_move) {
        return player_2_move + 3; // shape score + draw score
    }
    
    return player_2_move +  /* shape score */
        6 * ((player_1_move + 1 == player_2_move) || /* win score */
             (player_1_move == 3 && player_2_move == 1)
            );
}

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day02.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input");
        return 1;
    }
    
    unsigned int total_score = 0;
    
    char player_1_move;
    char player_2_move;
    while (fscanf(puzzle_input_file_ptr, "%c %c\n", &player_1_move, &player_2_move) != EOF) {
        total_score += get_round_score(player_1_move, player_2_move);      
    }
    printf("total score: %u", total_score);
    fclose(puzzle_input_file_ptr);
    return 0;
}