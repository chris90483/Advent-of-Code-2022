#include <stdio.h>

#define LOSE 1
#define DRAW 2
#define WIN  3

unsigned int get_round_score(char player_1_move, char desired_outcome) {
    player_1_move = player_1_move & 3; 
    desired_outcome = (desired_outcome - 23) & 3;
    
    char player_2_move;
    switch (desired_outcome) {
        case LOSE: player_2_move =  player_1_move - 1;      break;
        case DRAW: player_2_move =  player_1_move;          break;
        case WIN:  player_2_move = (player_1_move + 1) & 3; break;
    } 
    if (!player_2_move) {
        player_2_move = desired_outcome == WIN ? 1 : 3;
    }
    
    return ((desired_outcome - 1) * 3) + player_2_move;
}

int main() {
    FILE *puzzle_input_file_ptr = fopen("..\\inputs\\day02.txt", "r");
    if (puzzle_input_file_ptr == NULL) {
        printf("Unable to open puzzle input");
        return 1;
    }
    
    unsigned int total_score = 0;
    
    char player_1_move;
    char desired_outcome;
    while (fscanf(puzzle_input_file_ptr, "%c %c\n", &player_1_move, &desired_outcome) != EOF) {
        total_score += get_round_score(player_1_move, desired_outcome);      
    }
    printf("total score: %u", total_score);
    fclose(puzzle_input_file_ptr);
    return 0;
}