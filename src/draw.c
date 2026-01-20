#include "draw.h"

static inline void DrawLetterCells(LetterCell cells[NUM_GUESSES][NUM_LETTERS]){
    for (int r = 0; r < NUM_GUESSES; ++r){
        for(int c = 0; c < NUM_LETTERS; ++c){
            DrawLetterCell(&cells[r][c]);
        }
    }
}

void DrawMainGameplayScreen(LetterCell cells[NUM_GUESSES][NUM_LETTERS], Keyboard *keyb, int screenWidth, int screenHeight){
    DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
    DrawLetterCells(cells);
    DrawKeyboard(keyb);
}

void DrawRowShake(LetterCell cells[NUM_GUESSES][NUM_LETTERS], GameState *g){
    static int shakeDir = -1;
    // Slow down shaking ToDo: make smoother
    if((g->framesCounter/45)%2 == 0){
        for(int c = 0; c < NUM_LETTERS; ++c){
            DrawLetterCellWithSkew(&cells[g->guessingWordIdx][c], shakeDir*g->shakeSkew);
        }
        shakeDir *= -1;
    }
}