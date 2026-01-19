#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "cell.h"
#include <stdlib.h>
#include <string.h>

#define NUM_ROW_KEYS 9
#define TOP_ROW_MOD 1

typedef enum KeyboardRow {
    TOP,
    MIDDLE,
    BOTTOM,
    NUM_ROWS
} KeyboardRow;

typedef struct Keyboard {
    float positionY; // Will always be centered, so just need y offset
    Vector2 keySize;
    int fontSize;
    int keyPadding;
    Color primaryC;
    Color secondaryC;
    LetterCell **keys[NUM_ROWS];

} Keyboard;

Keyboard *createKeyboard(float positionY, Vector2 keySize, int fontSize, int keyPadding, Color primary, Color secondary);
void drawKeyboard(Keyboard *k);
void releaseKeyboard(Keyboard *k);

static const char *top_row_keys[NUM_ROW_KEYS+1] = {
    [0] = "Q",
    [1] = "W",
    [2] = "E",
    [3] = "R",
    [4] = "T",
    [5] = "Y",
    [6] = "U",
    [7] = "I",
    [8] = "O",
    [9] = "P"
};

static const char *mid_row_keys[NUM_ROW_KEYS] = {
    [0] = "A",
    [1] = "S",
    [2] = "D",
    [3] = "F",
    [4] = "G",
    [5] = "H",
    [6] = "J",
    [7] = "K",
    [8] = "L"
};

static const char *bottom_row_keys[NUM_ROW_KEYS] = {
    [0] = "#",
    [1] = "Z",
    [2] = "X",
    [3] = "C",
    [4] = "V",
    [5] = "B",
    [6] = "N",
    [7] = "M",
    [8] = "<"
};

#endif // KEYBOARD_H