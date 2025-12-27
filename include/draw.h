#ifndef DRAW_H
#define DRAW_H

#include "raylib.h"
#include "keyboard.h"
#include "globals.h"

void DrawMainGameplayScreen(LetterCell cells[NUM_GUESSES][NUM_LETTERS], Keyboard *keyb, int screenWidth, int screenHeight);
void DrawNotification(Notification n, LetterCell cells[NUM_GUESSES][NUM_LETTERS], int guessRowIdx);

#endif // DRAW_H