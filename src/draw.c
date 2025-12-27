#include "draw.h"

void DrawMainGameplayScreen(LetterCell cells[NUM_GUESSES][NUM_LETTERS], Keyboard *keyb, int screenWidth, int screenHeight){
    DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
    
    // Draw lettercells
    for (int r = 0; r < NUM_GUESSES; ++r){
        for(int c = 0; c < NUM_LETTERS; ++c){
            DrawLetterCell(&cells[r][c]);
        }
    }

    // Draw keyboard
    drawKeyboard(keyb);
}