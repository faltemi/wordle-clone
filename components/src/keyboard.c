#include "keyboard.h"
#include "inputProcessing.h"

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

static void DrawRow(Keyboard *k, KeyboardRow row, GameState *g){
    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);
    
    for(int i = 0; i < num_keys; ++i){
        k->keys[row][i]->draw(k->keys[row][i], g);
    }
}

void DrawKeyboard(Keyboard *k, GameState *g){
    DrawRow(k, TOP, g);
    DrawRow(k, MIDDLE, g);
    DrawRow(k, BOTTOM, g);
}

void FillRow(Keyboard *k, KeyboardRow row, GameState *g){
    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);
    Icon **curRow = malloc(num_keys * sizeof(Icon*));
    
    const char **row_key_map = GetKeyMapArray(row);
    const int offsetX = (GetScreenWidth() - (num_keys*k->keySize.x + k->keyPadding*(num_keys-1)))/2;
    const int padY = row == 0 ? 0 : k->keyPadding;
    for(int i = 0; i < num_keys; ++i){
        Vector2 cellPos = {i*(k->keySize.x + (i == 0 ? 0 : k->keyPadding)) + offsetX, (int)row*(k->keySize.y + padY) + k->positionY};
        Rectangle bounds = {cellPos.x, cellPos.y, k->keySize.x, k->keySize.y};
        Icon *newCell = MakeIcon(ICON_KEYB_LETTER, bounds, g);
        TextCopy(newCell->data.letterIcon->letter, row_key_map[i]);
        newCell->data.letterIcon->state = BEING_GUESSED;
        curRow[i] = newCell;
    }
    k->keys[row] = curRow;
}

Keyboard *CreateKeyboard(GameState *g){
    Keyboard *k = malloc(sizeof(Keyboard));
    k->positionY = g->keybPosY;
    k->fontSize = g->keybFontSize;
    k->keySize = (Vector2) {g->keybCellSize, g->keybCellSize};
    k->keyPadding = g->keybPadding;
    FillRow(k, TOP, g);
    FillRow(k, MIDDLE, g);
    FillRow(k, BOTTOM, g);
    return k;
}

void ProcessKeyClick(GameGrid *gameGrid, Keyboard *keyb, NotificationManager* notifMgr, GameState *g){
    for(int i = 0; i < NUM_ROWS; ++i){
        int num_keys = NUM_ROW_KEYS + (i == 0 ? 1 : 0);
        for(int j = 0; j < num_keys; ++j){
            if(CheckCollisionPointRec(GetMousePosition(),keyb->keys[i][j]->bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                // Key press logic: letter, enter, del
                if(strcmp(keyb->keys[i][j]->data.letterIcon->letter, g->enterKey) == 0){
                    GuessWord(gameGrid, notifMgr, g);
                }
                else if(strcmp(keyb->keys[i][j]->data.letterIcon->letter, g->deleteKey) == 0){
                    DeleteLetter(gameGrid, g);
                }
                else{
                    AddLetter(gameGrid, keyb->keys[i][j]->data.letterIcon->letter[0], g);
                }
            }
        }
    }
}

static void FreeRow(Keyboard *k, KeyboardRow row){
    if(k->keys[row] == NULL) return;

    int num_keys = NUM_ROW_KEYS + (row == TOP ? TOP_ROW_MOD : 0);

    for(int i = 0; i < num_keys; ++i){
        FreeIcon(k->keys[row][i]);
    }
    free(k->keys[row]);
}

void ReleaseKeyboard(Keyboard *k){
    FreeRow(k, TOP);
    FreeRow(k, MIDDLE);
    FreeRow(k, BOTTOM);
    free(k);
}
