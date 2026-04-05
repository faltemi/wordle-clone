#include "inputProcessing.h"
#include "gameGrid.h"
#include <stdio.h>
#include <stdbool.h>

static void GetWord(GameGrid *gameGrid, int guessRowIdx, char *outputBuffer){
    for(int i = 0; i < NUM_LETTERS; ++i){
        outputBuffer[i] = gameGrid->letterIcons[guessRowIdx][i]->data.letterIcon->letter[0];
    }
    outputBuffer[NUM_LETTERS] = '\0';
}

static bool IsValidHardModeGuess(GameGrid *gameGrid, NotificationManager *notiMgr, GameState *g){
    const char *ordinals[] = {"1st", "2nd", "3rd", "4th", "5th"};
    char guessedWord[NUM_LETTERS + 1];
    GetWord(gameGrid, g->guessRowIdx, guessedWord);

    // Check green-locked positions
    for(int i = 0; i < NUM_LETTERS; ++i){
        if(g->greenLocked[i] && guessedWord[i] != g->greenLocked[i]){
            snprintf(notiMgr->message, sizeof(notiMgr->message),
                     "%s letter must be %c", ordinals[i], g->greenLocked[i]);
            return false;
        }
    }

    // Check yellow-required letters
    for(int i = 0; i < g->yellowCount; ++i){
        bool found = false;
        for(int j = 0; j < NUM_LETTERS; ++j){
            if(guessedWord[j] == g->yellowRequired[i]){
                found = true;
                break;
            }
        }
        if(!found){
            snprintf(notiMgr->message, sizeof(notiMgr->message),
                     "Guess must contain %c", g->yellowRequired[i]);
            return false;
        }
    }

    return true;
}

void GuessWord(GameGrid *gameGrid, NotificationManager *notifMgr, GameState *g){
    if(g->guessLetterIdx == NUM_LETTERS){
        char guessedWord[NUM_LETTERS+1];
        GetWord(gameGrid, g->guessRowIdx, guessedWord);
        
        if(IsValidWord(g->wordList, guessedWord)){
            if(g->isHardMode && !IsValidHardModeGuess(gameGrid, notifMgr, g)){
                SetNotification(notifMgr, NOTIFY_HARDMODE_VIOLATION);
                return;
            }
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
    else if (IsKeyPressed(KEY_ESCAPE)){
        g->gameScreen = SETTINGS;
    }
}

// ToDo: struct for interactables instead of expanding func sig
void ProcessMouseInputs(GameGrid *gameGrid, Keyboard *keyb, NotificationManager* notifMgr, Icon *s, GameState *g){
    // Check for clicked keyboard key
    ProcessKeyClick(gameGrid, keyb, notifMgr, g);
    // Check for clicked settings icon
    // ToDo: POLISH: For draw check collision point and change color of bounds
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), s->bounds)){
        s->onClick(g);
    }
}