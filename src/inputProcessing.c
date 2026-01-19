#include "inputProcessing.h"

static void DeleteLetter(LetterCell cells[NUM_GUESSES][NUM_LETTERS], int guessRowIdx, int *guessLetterIdx){
    if(*guessLetterIdx != 0) (*guessLetterIdx)--;
    cells[guessRowIdx][*guessLetterIdx].letter[0] = '\0';
    cells[guessRowIdx][*guessLetterIdx].state = NO_GUESS;
}

static void AddLetter(LetterCell cells[NUM_GUESSES][NUM_LETTERS], char letter, int guessRowIdx, int *guessLetterIdx){
    if (letter >= 'a' && letter <= 'z') letter -= 32;
    if(*guessLetterIdx < NUM_LETTERS && letter >= 'A' && letter <= 'Z'){
        cells[guessRowIdx][*guessLetterIdx].letter[0] = letter;
        cells[guessRowIdx][*guessLetterIdx].letter[1] = '\0';
        cells[guessRowIdx][*guessLetterIdx].state = BEING_GUESSED;
        (*guessLetterIdx)++;
    }
}

static void GetWord(LetterCell cells[NUM_GUESSES][NUM_LETTERS], int guessRowIdx, char *outputBuffer){
    for(int i = 0; i < NUM_LETTERS; ++i){
        outputBuffer[i] = cells[guessRowIdx][i].letter[0];
    }
    outputBuffer[NUM_LETTERS] = '\0';
}

static void GuessWord(WordList *wordList, LetterCell cells[NUM_GUESSES][NUM_LETTERS], int guessRowIdx, int *guessLetterIdx, GameScreen *screen, NotificationManager* notifMgr){
    if(*guessLetterIdx == NUM_LETTERS){
        char guessedWord[NUM_LETTERS+1];
        GetWord(cells, guessRowIdx, guessedWord);
        
        if(IsValidWord(wordList, guessedWord)){
            // Change state to 'guessing', freeze input and guess each letter until done
            *screen = GUESSING;
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

void ProcessKeyboardInputs(WordList *wordList, LetterCell cells[NUM_GUESSES][NUM_LETTERS], int guessRowIdx, int *guessLetterIdx, NotificationManager* notifMgr, GameState *g){
    // Buffer of keys pressed until empty then 0
    int key = GetCharPressed();
    while(key > 0){
        if((key >= 32) && (key <= 125)){
            AddLetter(cells, (char)key, guessRowIdx, guessLetterIdx);
        }
        key = GetCharPressed();
    }
    
    if (IsKeyPressed(KEY_ENTER)){
        GuessWord(wordList, cells, guessRowIdx, guessLetterIdx, &g->gameScreen, notifMgr);
    }
    else if (IsKeyPressed(KEY_BACKSPACE)){
        DeleteLetter(cells, guessRowIdx, guessLetterIdx);
    }
}

// ToDo: struct for interactables instead of expanding func sig
void ProcessMouseInputs(WordList *wordList, LetterCell cells[NUM_GUESSES][NUM_LETTERS], Keyboard *keyb, int guessRowIdx, int *guessLetterIdx, NotificationManager* notifMgr, Icon *s, GameState *g){
    // Check for clicked keyboard key
    for(int i = 0; i < NUM_ROWS; ++i){
        int num_keys = NUM_ROW_KEYS + (i == 0 ? 1 : 0);
        for(int j = 0; j < num_keys; ++j){
            if(CheckCollisionPointRec(GetMousePosition(),keyb->keys[i][j]->bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                // Key press logic: letter, enter, del
                if(strcmp(keyb->keys[i][j]->letter, g->enterKey) == 0){
                    GuessWord(wordList, cells, guessRowIdx, guessLetterIdx, &g->gameScreen, notifMgr);
                }
                else if(strcmp(keyb->keys[i][j]->letter, g->deleteKey) == 0){
                    DeleteLetter(cells, guessRowIdx, guessLetterIdx);
                }
                else{
                    AddLetter(cells, keyb->keys[i][j]->letter[0], guessRowIdx, guessLetterIdx);
                }
            }
        }
    }
    // Check for clicked settings icon
    // ToDo: POLISH: For draw check collision point and change color of bounds
    if(CheckCollisionPointRec(GetMousePosition(), s->bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        g->gameScreen = SETTINGS;
    }
}