#define TERM_CLEAR "\x1b[1;1H\x1b[2J"
#define TERM_NEWLINE '\n'

#define STATE_RUNNING 0
#define STATE_X_VICTORY 1
#define STATE_O_VICTORY 2
#define STATE_DRAW 3

#define PLAYER_X 0
#define PLAYER_O 1

#define BOARD_SIZE 9

#define SPACE_MIN 0
#define SPACE_MAX 8
#define SPACE_FREE ' '
#define SPACE_INVALID -1

struct t_game {
    char board[BOARD_SIZE];
    int moves;
    int player;
    int state;
};

void init_game(struct t_game *game);
void game_loop(struct t_game *game);
void print_board(struct t_game *game);
void get_move(struct t_game *game);
void check_state(struct t_game *game);
int check_spaces(char a, char b, char c);
void end_game(struct t_game *game);
