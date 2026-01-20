#include "inputProcessing.h"
#include "gameGrid.h"

// ToDO: This should be a game grid or letter icon method?
static void DeleteLetter(GameGrid *gameGrid, GameState *g){
    if(g->guessLetterIdx != 0) (g->guessLetterIdx)--;
    gameGrid->letterIcons[g->guessRowIdx][g->guessLetterIdx]->data.letterIcon->letter[0] = '\0';
    gameGrid->letterIcons[g->guessRowIdx][g->guessLetterIdx]->data.letterIcon->state = NO_GUESS;
}

static void AddLetter(GameGrid *gameGrid, char letter, GameState *g){
    if (letter >= 'a' && letter <= 'z') letter -= 32;
    if(g->guessLetterIdx < NUM_LETTERS && letter >= 'A' && letter <= 'Z'){
        gameGrid->letterIcons[g->guessRowIdx][g->guessLetterIdx]->data.letterIcon->letter[0] = letter;
        gameGrid->letterIcons[g->guessRowIdx][g->guessLetterIdx]->data.letterIcon->letter[1] = '\0';
        gameGrid->letterIcons[g->guessRowIdx][g->guessLetterIdx]->data.letterIcon->state = BEING_GUESSED;
        g->guessLetterIdx++;
    }
}

static void GetWord(GameGrid *gameGrid, int guessRowIdx, char *outputBuffer){
    for(int i = 0; i < NUM_LETTERS; ++i){
        outputBuffer[i] = gameGrid->letterIcons[guessRowIdx][i]->data.letterIcon->letter[0];
    }
    outputBuffer[NUM_LETTERS] = '\0';
}

static void GuessWord(GameGrid *gameGrid, NotificationManager* notifMgr, GameState *g){
    if(g->guessLetterIdx == NUM_LETTERS){
        char guessedWord[NUM_LETTERS+1];
        GetWord(gameGrid, g->guessRowIdx, guessedWord);
        
        if(IsValidWord(g->wordList, guessedWord)){
            // Change state to 'guessing', freeze input and guess each letter until done
            g->gameScreen = GUESSING;
        }
        else{
            // Need to display invalid word or something, get info out via flag?
            SetNotification(notifMgr, NOTIFY_INVALID_WORD);
        }
    }
    else{
        // Shake row and display 'not enough letters'
        SetNotification(notifMgr, NOTIFY_NOT_ENOUGH_LETTERS);
    }
}

void ProcessKeyboardInputs(GameGrid *gameGrid, NotificationManager* notifMgr, GameState *g){
    // Buffer of keys pressed until empty then 0
    int key = GetCharPressed();
    while(key > 0){
        if((key >= 32) && (key <= 125)){
            AddLetter(gameGrid, (char)key, g);
        }
        key = GetCharPressed();
    }
    
    if (IsKeyPressed(KEY_ENTER)){
        GuessWord(gameGrid, notifMgr, g);
    }
    else if (IsKeyPressed(KEY_BACKSPACE)){
        DeleteLetter(gameGrid, g);
    }
}

// ToDo: struct for interactables instead of expanding func sig
void ProcessMouseInputs(GameGrid *gameGrid, Keyboard *keyb, NotificationManager* notifMgr, Icon *s, GameState *g){
    // Check for clicked keyboard key
    for(int i = 0; i < NUM_ROWS; ++i){
        int num_keys = NUM_ROW_KEYS + (i == 0 ? 1 : 0);
        for(int j = 0; j < num_keys; ++j){
            if(CheckCollisionPointRec(GetMousePosition(),keyb->keys[i][j]->bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                // Key press logic: letter, enter, del
                if(strcmp(keyb->keys[i][j]->letter, g->enterKey) == 0){
                    GuessWord(gameGrid, notifMgr, g);
                }
                else if(strcmp(keyb->keys[i][j]->letter, g->deleteKey) == 0){
                    DeleteLetter(gameGrid, g);
                }
                else{
                    AddLetter(gameGrid, keyb->keys[i][j]->letter[0], g);
                }
            }
        }
    }
    // Check for clicked settings icon
    // ToDo: POLISH: For draw check collision point and change color of bounds
    if(CheckCollisionPointRec(GetMousePosition(), s->bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        s->onClick(g);
    }
}