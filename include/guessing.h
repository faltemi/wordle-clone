#ifndef GUESSING_H
#define GUESSING_H

#include "globals.h"
#include "gameState.h"
#include "keyboard.h"
#include "cell.h"

void ProcessGuess(LetterCell cells[NUM_GUESSES][NUM_LETTERS], const char *targetWord, GameState *g);

#endif // GUESSING_H