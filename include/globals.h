#ifndef GLOBALS_H
#define GLOBALS_H

#define SCREEN_HEIGHT       600
#define SCREEN_WIDTH        800
#define WINDOW_TITLE        "Wordle Clone"
#define NUM_GUESSES         6
#define NUM_LETTERS         5
#define CELL_SIZE           50
#define CELL_Y_OFFSET       50
#define CELL_PADDING        5
#define LETTER_SIZE         20
#define DELETE "<"
#define ENTER "#"
#define WORDSPATH "data/words.txt"

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, GUESSING, LOSE, WIN, ENDING } GameScreen;

typedef enum Notification {
    NONE,
    NOT_ENOUGH_LETTERS,
    INVALID_WORD
} Notification;

#endif // GLOBALS_H