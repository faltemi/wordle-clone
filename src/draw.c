#include "draw.h"

static inline void DrawLetterCells(LetterCell cells[NUM_GUESSES][NUM_LETTERS]){
    for (int r = 0; r < NUM_GUESSES; ++r){
        for(int c = 0; c < NUM_LETTERS; ++c){
            DrawLetterCell(&cells[r][c]);
        }
    }
}

void DrawMainGameplayScreen(GameGrid *gameGrid, Keyboard *keyb, GameState *g){
    DrawRectangle(0, 0, g->screenWidth, g->screenHeight, RAYWHITE);
    DrawGameGrid(gameGrid, g);
    DrawKeyboard(keyb);
}

void DrawRowShake(LetterCell cells[NUM_GUESSES][NUM_LETTERS], GameState *g){
    static int shakeDir = -1;
    // Slow down shaking ToDo: make smoother
    if((g->framesCounter/45)%2 == 0){
        for(int c = 0; c < NUM_LETTERS; ++c){
            DrawLetterCellWithSkew(&cells[g->guessRowIdx][c], shakeDir*g->shakeSkew);
        }
        shakeDir *= -1;
    }
}