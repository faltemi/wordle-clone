#ifndef INPUTPROCESSING_H
#define INPUTPROCESSING_H

#include "raylib.h"
#include "cell.h"
#include "keyboard.h"
#include "globals.h"
#include "wordList.h"

void ProcessKeyboardInputs(WordList *wordList, LetterCell cells[NUM_GUESSES][NUM_LETTERS], GameScreen *screen, int guessRowIdx, int *guessLetterIdx);
void ProcessMouseInputs(WordList *wordList, LetterCell cells[NUM_GUESSES][NUM_LETTERS], Keyboard *keyb, GameScreen *screen, int guessRowIdx, int *guessLetterIdx);

#endif // INPUTPROCESSING_H