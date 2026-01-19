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

static void drawRow(Keyboard *k, KeyboardRow row){
    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);
    
    for(int i = 0; i < num_keys; ++i){
        DrawLetterCell(k->keys[row][i]);
    }
}

void drawKeyboard(Keyboard *k){
    drawRow(k, TOP);
    drawRow(k, MIDDLE);
    drawRow(k, BOTTOM);
}

void fillRow(Keyboard *k, KeyboardRow row){
    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);
    LetterCell **curRow = malloc(num_keys * sizeof(LetterCell*));
    
    const char **row_key_map = getKeyMapArr(row);
    const int offsetX = (GetScreenWidth() - (num_keys*k->keySize.x + k->keyPadding*(num_keys-1)))/2;
    const int padY = row == 0 ? 0 : k->keyPadding;
    for(int i = 0; i < num_keys; ++i){
        LetterCell *newCell = malloc(sizeof(LetterCell));
        Vector2 cellPos = {i*(k->keySize.x + (i == 0 ? 0 : k->keyPadding)) + offsetX, (int)row*(k->keySize.y + padY) + k->positionY};
        InitLetterCell(newCell, cellPos, k->keySize, k->fontSize);
        TextCopy(newCell->letter, row_key_map[i]);
        newCell->state = KEYBOARD;
        curRow[i] = newCell;
    }
    k->keys[row] = curRow;
}

Keyboard *createKeyboard(float postionY, Vector2 keySize, int fontSize, int keyPadding, Color primary, Color secondary){
    Keyboard *k = malloc(sizeof(Keyboard));
    k->positionY = postionY;
    k->fontSize = fontSize;
    k->keySize = keySize;
    k->keyPadding = keyPadding;
    k->primaryC = primary;
    k->secondaryC = secondary;
    fillRow(k, TOP);
    fillRow(k, MIDDLE);
    fillRow(k, BOTTOM);
    // Init first row
    return k;
}

static void freeRow(Keyboard *k, KeyboardRow row){
    if(k->keys[row] == NULL) return;

    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);

    for(int i = 0; i < num_keys; ++i){
        free(k->keys[row][i]);
    }
    free(k->keys[row]);
}

// ToDo: update destructor
void releaseKeyboard(Keyboard *k){
    freeRow(k, TOP);
    freeRow(k, MIDDLE);
    freeRow(k, BOTTOM);
    free(k);
}
