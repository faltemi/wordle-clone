#include "keyboard.h"

static const char *topRowKeys[NUM_ROW_KEYS+1] = {
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

static const char *midRowKeys[NUM_ROW_KEYS] = {
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

static const char *bottomRowKeys[NUM_ROW_KEYS] = {
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

static const char **GetKeyMapArray(KeyboardRow row){
    switch (row)
    {
    case TOP:
        return topRowKeys;
        break;
    case MIDDLE:
        return midRowKeys;
        break;
    case BOTTOM:
        return bottomRowKeys;
        break;
    default:
        return NULL;
        break;
    }
}

static void DrawRow(Keyboard *k, KeyboardRow row){
    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);
    
    for(int i = 0; i < num_keys; ++i){
        DrawLetterCell(k->keys[row][i]);
    }
}

void DrawKeyboard(Keyboard *k){
    DrawRow(k, TOP);
    DrawRow(k, MIDDLE);
    DrawRow(k, BOTTOM);
}

void FillRow(Keyboard *k, KeyboardRow row){
    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);
    LetterCell **curRow = malloc(num_keys * sizeof(LetterCell*));
    
    const char **row_key_map = GetKeyMapArray(row);
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

Keyboard *CreateKeyboard(float postionY, Vector2 keySize, int fontSize, int keyPadding, Color primary, Color secondary){
    Keyboard *k = malloc(sizeof(Keyboard));
    k->positionY = postionY;
    k->fontSize = fontSize;
    k->keySize = keySize;
    k->keyPadding = keyPadding;
    k->primaryC = primary;
    k->secondaryC = secondary;
    FillRow(k, TOP);
    FillRow(k, MIDDLE);
    FillRow(k, BOTTOM);
    return k;
}

static void FreeRow(Keyboard *k, KeyboardRow row){
    if(k->keys[row] == NULL) return;

    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);

    for(int i = 0; i < num_keys; ++i){
        free(k->keys[row][i]);
    }
    free(k->keys[row]);
}

void ReleaseKeyboard(Keyboard *k){
    FreeRow(k, TOP);
    FreeRow(k, MIDDLE);
    FreeRow(k, BOTTOM);
    free(k);
}
