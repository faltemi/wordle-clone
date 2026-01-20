#ifndef INPUTPROCESSING_H
#define INPUTPROCESSING_H

#include "raylib.h"
#include "cell.h"
#include "keyboard.h"
#include "globals.h"
#include "wordList.h"
#include "notification.h"
#include "gameState.h"
#include "icon.h"

void ProcessKeyboardInputs(WordList *wordList, LetterCell cells[NUM_GUESSES][NUM_LETTERS], NotificationManager *notifMgr, GameState *g);
void ProcessMouseInputs(WordList *wordList, LetterCell cells[NUM_GUESSES][NUM_LETTERS], Keyboard *keyb, NotificationManager *notifMgr, Icon *s, GameState *g);
// Process settings inputs MOUSE ONLY
#endif // INPUTPROCESSING_H