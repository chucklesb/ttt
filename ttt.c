#include <stdio.h>
#include "ttt.h"

int main() {
    struct t_game game;

    init_game(&game);
    game_loop(&game);
    end_game(&game);

    return(0);
}

void init_game(struct t_game *game) {
    game->moves = 0;
    game->player = PLAYER_X;
    game->state = STATE_RUNNING;

    // initialize board
    for(int i = 0; i < BOARD_SIZE; i++)
        game->board[i] = SPACE_FREE;

    return;
}

void game_loop(struct t_game *game) {
    do {
        print_board(game);
        get_move(game);
        check_state(game);
    } while(game->state == STATE_RUNNING);
}

void print_board(struct t_game *game) {
    printf(TERM_CLEAR);
    printf("%c|%c|%c\n-----\n", game->board[0], game->board[1], game->board[2]);
    printf("%c|%c|%c\n-----\n", game->board[3], game->board[4], game->board[5]);
    printf("%c|%c|%c\n\n",      game->board[6], game->board[7], game->board[8]);
	
    return;
}

void get_move(struct t_game *game) {
    int space;
    char symbol;

    switch(game->player) {
        case PLAYER_X: symbol = 'X'; break;
        case PLAYER_O: symbol = 'O'; break;
    }

    do {
        printf("Enter a move for %c: ", symbol);
        space = getchar() - '1';		// get first char, subtract 1
        while(getchar() != TERM_NEWLINE);	// discard remaining chars
        if(game->board[space] != SPACE_FREE)
            space = SPACE_INVALID;
    } while(space < SPACE_MIN || space > SPACE_MAX);

    game->board[space] = symbol;		// place player symbol
    game->moves++;				// track how many symbols have been placed
    game->player = !game->player;		// swap player turns

    return;
}

void check_state(struct t_game *game) {
    int i, result = 0;

    // check for horizontal win conditions
    for(i = 0; i < 9; i+=3)
        result += check_spaces(game->board[i+0], game->board[i+1], game->board[i+2]);

    // check for vertical win conditions
    for(i = 0; i < 3; i++)
        result += check_spaces(game->board[i+0], game->board[i+3], game->board[i+6]);

    // check for diagonal win conditions
    result += check_spaces(game->board[0], game->board[4], game->board[8]);
    result += check_spaces(game->board[2], game->board[4], game->board[6]);

    // set game state
    if(result) game->state = (game->player == PLAYER_O) ? STATE_X_VICTORY : STATE_O_VICTORY;
    else if(game->moves >= BOARD_SIZE) game->state = STATE_DRAW;

    return;
}

int check_spaces(char a, char b, char c) {
    if(a != SPACE_FREE && a == b && b == c) return(1);
    else return(0);
}

void end_game(struct t_game *game) {
    print_board(game);

    switch(game->state) {
        case STATE_X_VICTORY: printf("X victory!\n"); break;
        case STATE_O_VICTORY: printf("O victory!\n"); break;
        case STATE_DRAW: printf("Draw!\n"); break;
    }

    return;
}
