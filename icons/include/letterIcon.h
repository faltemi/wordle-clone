#ifndef LETTER_ICON_H
#define LETTER_ICON_H

#include "raylib.h"
#include "gameState.h"

typedef struct Icon Icon;

typedef enum LetterState {
    NO_GUESS,
    WRONG_POS,
    CORRECT,
    INCORRECT,
    BEING_GUESSED,
    //KEYBOARD
} LetterState;

typedef struct LetterIcon {
    Rectangle bounds;
    char letter[8];
    int fontSize;
    LetterState state;
} LetterIcon;

LetterIcon *MakeLetterIcon(Rectangle bounds, GameState *g);
// Handle skew
void DrawLetterIconWithSkew(LetterIcon *l, GameState *g);
void DrawLetterIcon(Icon *i, GameState *g);

#endif // LETER_ICON_H