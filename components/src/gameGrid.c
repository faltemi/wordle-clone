#include "gameGrid.h"
#include <stdlib.h>

void DeleteLetter(GameGrid *gameGrid, GameState *g){
    if(g->guessLetterIdx != 0) (g->guessLetterIdx)--;
    gameGrid->letterIcons[g->guessRowIdx][g->guessLetterIdx]->data.letterIcon->letter[0] = '\0';
    gameGrid->letterIcons[g->guessRowIdx][g->guessLetterIdx]->data.letterIcon->state = NO_GUESS;
}

void AddLetter(GameGrid *gameGrid, char letter, GameState *g){
    if (letter >= 'a' && letter <= 'z') letter -= 32;
    if(g->guessLetterIdx < NUM_LETTERS && letter >= 'A' && letter <= 'Z'){
        gameGrid->letterIcons[g->guessRowIdx][g->guessLetterIdx]->data.letterIcon->letter[0] = letter;
        gameGrid->letterIcons[g->guessRowIdx][g->guessLetterIdx]->data.letterIcon->letter[1] = '\0';
        gameGrid->letterIcons[g->guessRowIdx][g->guessLetterIdx]->data.letterIcon->state = BEING_GUESSED;
        g->guessLetterIdx++;
    }
}

GameGrid *MakeGameGrid(GameState *g){
    GameGrid *grid = malloc(sizeof(GameGrid));

    for (int r = 0; r < NUM_GUESSES; r++){
        for (int c = 0; c < NUM_LETTERS; c++){
            const int paddingX = c == 0 ? 0 : g->cellPadding;
            const int paddingY = r == 0 ? 0 : g->cellPadding;

            const int totalW = NUM_LETTERS*g->cellSize + g->cellPadding*(NUM_LETTERS-1);
            const int offsetX = (g->screenWidth - totalW)/2;

            const int posX = c*(g->cellSize + paddingX) + offsetX;
            const int posY = r*(g->cellSize + paddingY) + g->cellOffsetY;
            Rectangle bounds = (Rectangle){posX, posY, g->cellSize, g->cellSize};
            grid->letterIcons[r][c] = MakeIcon(ICON_LETTER, bounds, g);
        }
    }
    return grid;
}

void DrawGameGrid(GameGrid *grid, GameState *g){
    for (int r = 0; r < NUM_GUESSES; ++r){
        for(int c = 0; c < NUM_LETTERS; ++c){
            grid->letterIcons[r][c]->draw(grid->letterIcons[r][c], g);
        }
    }
}

void ShakeRow(GameGrid *grid, GameState *g){
    static int shakeDir = -1;
    // Slow down shaking ToDo: make smoother
    if((g->framesCounter/45)%2 == 0){
        for(int c = 0; c < NUM_LETTERS; ++c){
            g->shakeSkew *= shakeDir;
            DrawLetterIconWithSkew(grid->letterIcons[g->guessRowIdx][c]->data.letterIcon, g);
        }
        shakeDir *= -1;
    }
}

void ResetGrid(GameGrid *grid){
    for (int r = 0; r < NUM_GUESSES; r++){
        for (int c = 0; c < NUM_LETTERS; c++){
            grid->letterIcons[r][c]->data.letterIcon->state = NO_GUESS;
            grid->letterIcons[r][c]->data.letterIcon->letter[0] = '\0';
        }
    }
}

void FreeGameGrid(GameGrid *grid){
    for (int r = 0; r < NUM_GUESSES; ++r){
        for (int c = 0; c < NUM_LETTERS; ++c){
            FreeIcon(grid->letterIcons[r][c]);
        }
    }
    free(grid);
}