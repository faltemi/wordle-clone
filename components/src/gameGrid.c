#include "gameGrid.h"
#include <stdlib.h>

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

GameGrid *FreeGameGrid(GameGrid *grid){
    for (int r = 0; r < NUM_GUESSES; ++r){
        for (int c = 0; c < NUM_LETTERS; ++c){
            FreeIcon(grid->letterIcons[r][c]);
        }
    }
    free(grid);
}