#ifndef GLOBALS_H
#define GLOBALS_H

#define SCREEN_HEIGHT       600
#define SCREEN_WIDTH        800
#define WINDOW_TITLE        "Wordle Clone"

#define NUM_GUESSES         6
#define NUM_LETTERS         5

#define CELL_SIZE           50
#define CELL_Y_OFFSET       70
#define CELL_PADDING        5
#define LETTER_SIZE         20

#define KEYB_POS_Y          430
#define KEYB_CELL_SIZE      40
#define SHAKE_SKEW          5
#define SHAKE_DURATION      1.0f

#define NOTIF_POS_Y         20
#define NOTIF_PAD           20

#define DELETE              "<"
#define ENTER               "#"
#define WORDSPATH           "data/words.txt"

#define RESTART_Y_OFFSET    100
#define RESTART_TEXT_SIZE   20
#define END_TEXT_SIZE       40
#define END_TEXT_Y_OFFSET   10

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, GUESSING, LOSE, WIN, ENDING } GameScreen;

#endif // GLOBALS_H