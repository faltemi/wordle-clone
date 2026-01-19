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

#endif // KEYBOARD_H