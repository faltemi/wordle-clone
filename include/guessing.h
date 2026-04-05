#ifndef GUESSING_H
#define GUESSING_H

#include "globals.h"
#include "gameState.h"
#include "gameGrid.h"
#include "keyboard.h"

void ProcessGuess(GameGrid *gameGrid, GameState *g, Keyboard *k);

#endif // GUESSING_H