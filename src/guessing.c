#include "guessing.h"

void ProcessGuess(LetterCell cells[NUM_GUESSES][NUM_LETTERS], GameScreen *screen, const char *targetWord, int *guessRowIdx, int *guessLetterIdx, int *guessingWordIndex, int *numCorrect){
    if(*guessingWordIndex < NUM_LETTERS){
        // Same letter
        if(cells[*guessRowIdx][*guessingWordIndex].letter[0] == targetWord[*guessingWordIndex]){
            cells[*guessRowIdx][*guessingWordIndex].state = CORRECT;
            (*numCorrect)++;
        }
        else{
            bool letterInWord = false;
            for(int i = 0; i < NUM_LETTERS; ++i){
                if(cells[*guessRowIdx][*guessingWordIndex].letter[0] == targetWord[i]){
                    letterInWord = true;
                    break;
                }
            }
            cells[*guessRowIdx][*guessingWordIndex].state = letterInWord ? WRONG_POS : INCORRECT;
        }
        (*guessingWordIndex)++;
    }
    else{
        if(*numCorrect == NUM_LETTERS){
            // ToDo: Win state/win screen
        }
        *guessingWordIndex = 0;
        (*numCorrect) = 0;
        (*guessRowIdx)++;
        *guessLetterIdx = 0;
        *screen = *guessRowIdx == NUM_GUESSES ? LOSE : GAMEPLAY;
    }
}