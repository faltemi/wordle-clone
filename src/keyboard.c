#include "keyboard.h"

Keyboard *createKeyboard(Vector2 postion){
    Keyboard *keyboard = malloc(sizeof(Keyboard));
    keyboard->position = postion;
    // Init first row
    return keyboard;
}

// ToDo: update destructor
void releaseKeyboard(Keyboard *k){
    free(k);
}

// ToDo: Make generic
void fillTopRow(Keyboard *k){
    LetterCell *firstRow[TOP_ROW_KEYS];
    for(int i = 0; i < TOP_ROW_KEYS; ++i){
        LetterCell *newCell;
        InitLetterCell(newCell, 10, 10, 0, 0, 4);
        newCell->letter = top_row_keys[i];
        firstRow[i] = newCell;
    }
    k->keys[0] = firstRow;
}