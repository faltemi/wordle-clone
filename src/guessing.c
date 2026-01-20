#include "guessing.h"

void ProcessGuess(LetterCell cells[NUM_GUESSES][NUM_LETTERS], const char *targetWord, GameState *g){
    if(g->guessingWordIdx < NUM_LETTERS){
        // Same letter
        if(cells[g->guessRowIdx][g->guessingWordIdx].letter[0] == targetWord[g->guessingWordIdx]){
            cells[g->guessRowIdx][g->guessingWordIdx].state = CORRECT;
            g->numLettersCorrect++;
        }
        else{
            bool letterInWord = false;
            for(int i = 0; i < NUM_LETTERS; ++i){
                if(cells[g->guessRowIdx][g->guessingWordIdx].letter[0] == targetWord[i]){
                    letterInWord = true;
                    break;
                }
            }
            cells[g->guessRowIdx][g->guessingWordIdx].state = letterInWord ? WRONG_POS : INCORRECT;
        }
        (g->guessingWordIdx)++;
    }
    else{
        if(g->numLettersCorrect == NUM_LETTERS){
            g->gameScreen = WIN;
            return;
        }
        g->guessingWordIdx = 0;
        g->numLettersCorrect = 0;
        g->guessRowIdx++;
        g->guessLetterIdx = 0;
        g->gameScreen = g->guessRowIdx == NUM_GUESSES ? LOSE : GAMEPLAY;
    }
}