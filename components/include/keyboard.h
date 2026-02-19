#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "icon.h"
#include "gameGrid.h"
#include "notificationManager.h"
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
    float positionY;
    Vector2 keySize;
    int fontSize;
    int keyPadding;
    Icon **keys[NUM_ROWS];

} Keyboard;

Keyboard *CreateKeyboard(GameState *g);
void AssignKeyState(Keyboard *k, char letter, LetterState state);
void ProcessKeyClick(GameGrid *gameGrid, Keyboard *keyb, NotificationManager* notifMgr, GameState *g);
void ResetKeyboard(Keyboard *k);
void DrawKeyboard(Keyboard *k, GameState *g);
void ReleaseKeyboard(Keyboard *k);

#endif // KEYBOARD_H