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

void DrawNotification(Notification n, LetterCell cells[NUM_GUESSES][NUM_LETTERS], int guessRowIdx){
    switch(n){
        case NONE:
        {break;}
        case NOT_ENOUGH_LETTERS:
        {
            // Display message
            // Make it width of text with padding
            DrawRectangle(SCREEN_WIDTH/4, 20, 80, 40, WHITE);
            DrawText("Not Enough Letters", SCREEN_WIDTH/4, 20, 30, BLACK);
            // Shake 
        }break;
        default: break;
    }
}