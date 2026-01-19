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
    drawKeyboard(keyb);
}

void DrawRowShake(LetterCell cells[NUM_GUESSES][NUM_LETTERS], int row, int framesCounter){
    // Will need to have buffer before changing dir
    static int shakeDir = -1;
    // Slow down shaking ToDo: make smoother
    if((framesCounter/45)%2 == 0){
        for(int c = 0; c < NUM_LETTERS; ++c){
            DrawLetterCellWithSkew(&cells[row][c], shakeDir*SHAKE_SKEW);
        }
        shakeDir *= -1;
    }
}