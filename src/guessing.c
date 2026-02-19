#include "guessing.h"

void ProcessGuess(GameGrid *gameGrid, GameState *g, Keyboard *k){
    if(g->guessingWordIdx < NUM_LETTERS){
        // Same letter
        // ToDo: Hide verbose calls with helper functions?
        if(gameGrid->letterIcons[g->guessRowIdx][g->guessingWordIdx]->data.letterIcon->letter[0] == g->targetWord[g->guessingWordIdx]){
            gameGrid->letterIcons[g->guessRowIdx][g->guessingWordIdx]->data.letterIcon->state = CORRECT;
            AssignKeyState(k, gameGrid->letterIcons[g->guessRowIdx][g->guessingWordIdx]->data.letterIcon->letter[0], CORRECT);
            g->numLettersCorrect++;
        }
        else{
            bool letterInWord = false;
            for(int i = 0; i < NUM_LETTERS; ++i){
                if(gameGrid->letterIcons[g->guessRowIdx][g->guessingWordIdx]->data.letterIcon->letter[0] == g->targetWord[i]){
                    letterInWord = true;
                    break;
                }
            }
            gameGrid->letterIcons[g->guessRowIdx][g->guessingWordIdx]->data.letterIcon->state = letterInWord ? WRONG_POS : INCORRECT;
            AssignKeyState(k,gameGrid->letterIcons[g->guessRowIdx][g->guessingWordIdx]->data.letterIcon->letter[0], (letterInWord ? WRONG_POS : INCORRECT));
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