#ifndef GUESSING_H
#define GUESSING_H

#include "globals.h"
#include "keyboard.h"
#include "cell.h"

void ProcessGuess(LetterCell cells[NUM_GUESSES][NUM_LETTERS], GameScreen *screen, const char *targetWord, int *guessRowIdx, int *guessLetterIdx, int *guessingWordIndex, int *numCorrect);

#endif // GUESSING_H