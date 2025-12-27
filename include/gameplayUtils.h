#ifndef GAMEPLAYUTILS_H
#define GAMEPLAYUTILS_H

#include "raylib.h"
#include "cell.h"
#include "keyboard.h"
#include "globals.h"

void ProcessKeyboardInputs(LetterCell cells[NUM_GUESSES][NUM_LETTERS], GameScreen *screen, int guessRowIdx, int *guessLetterIdx);
void ProcessMouseInputs(LetterCell cells[NUM_GUESSES][NUM_LETTERS], Keyboard *keyb, GameScreen *screen, int guessRowIdx, int *guessLetterIdx);

#endif // GAMEPLAYUTILS_H