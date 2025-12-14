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

static const char *getKeyMapArr(KeyboardRow row){
    switch (row)
    {
    case TOP:
        return top_row_keys;
        break;
    case MIDDLE:
        return mid_row_keys;
        break;
    case BOTTOM:
        return bottom_row_keys;
        break;
    default:
        return NULL;
        break;
    }
}

void fillRow(Keyboard *k, KeyboardRow row){
    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);
    LetterCell *curRow[num_keys];
    
    const char *row_key_map = getKeyMapArr(row);

    for(int i = 0; i < num_keys; ++i){
        LetterCell *newCell;
        InitLetterCell(newCell, 10, 10, 0, 0, 4);
        newCell->letter = row_key_map[i];

        curRow[i] = newCell;
    }
    k->keys[row] = curRow;
}