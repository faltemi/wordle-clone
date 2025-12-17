#include "keyboard.h"

static const char **getKeyMapArr(KeyboardRow row){
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
    
    const char **row_key_map = getKeyMapArr(row);

    for(int i = 0; i < num_keys; ++i){
        LetterCell *newCell = malloc(sizeof(LetterCell));
        Vector2 cellSize = {10, 10}; // ToDo: Clean this
        Vector2 cellPos = {0, 0};
        InitLetterCell(newCell, cellPos, cellSize, 4);
        newCell->letter = strdup(row_key_map[i]); // This might be POSIX only

        curRow[i] = newCell;
    }
    k->keys[row] = curRow;
}

Keyboard *createKeyboard(Vector2 postion, Vector2 keySize, int keyPadding, Color primary, Color secondary){
    Keyboard *keyboard = malloc(sizeof(Keyboard));
    keyboard->position = postion;
    keyboard->keySize = keySize;
    keyboard->primaryC = primary;
    keyboard->secondaryC = secondary;
    fillRow(keyboard, TOP);
    fillRow(keyboard, MIDDLE);
    fillRow(keyboard, BOTTOM);
    // Init first row
    return keyboard;
}

static void freeRow(Keyboard *k, KeyboardRow row){
    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);
    
    for(int i = 0; i < num_keys; ++i){
        free(k->keys[row][i]);
    }
}

// ToDo: update destructor
void releaseKeyboard(Keyboard *k){
    freeRow(k, TOP);
    freeRow(k, MIDDLE);
    freeRow(k, BOTTOM);
    free(k);
}
