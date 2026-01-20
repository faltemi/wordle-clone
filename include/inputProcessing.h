#ifndef INPUTPROCESSING_H
#define INPUTPROCESSING_H

#include "raylib.h"
#include "cell.h"
#include "keyboard.h"
#include "globals.h"
#include "wordList.h"
#include "notification.h"
#include "gameState.h"
#include "gameGrid.h"
#include "icon.h"

void ProcessKeyboardInputs(GameGrid *gameGrid, NotificationManager *notifMgr, GameState *g);
void ProcessMouseInputs(GameGrid *gameGrid, Keyboard *keyb, NotificationManager *notifMgr, Icon *s, GameState *g);
// Process settings inputs MOUSE ONLY
#endif // INPUTPROCESSING_H